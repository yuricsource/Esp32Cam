

#include <stdio.h>
#include <string.h>

#include "Camera.h"
#include "nvs_flash.h"
#include "tcpip_adapter.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "Camera/Driver/esp_camera.h"
// #include "bitmap.h"
// #include "led.h"
// #include "qr_recoginize.h"
#include "string.h"
// #include "bitmap.h"

// static const char *STREAM_CONTENT_TYPE =
//     "multipart/x-mixed-replace; boundary=123456789000000000000987654321";

// static const char *STREAM_BOUNDARY = "--123456789000000000000987654321";
// static EventGroupHandle_t s_wifi_event_group;

// static const int CONNECTED_BIT = BIT0;
// static ip4_addr_t s_ip_addr;
// static camera_pixelformat_t s_pixel_format;

// bitmap_header_t *bmp_create_header(int w, int h)
// {
//     bitmap_header_t *pbitmap = (bitmap_header_t *)calloc(1, sizeof(bitmap_header_t));
//     int _pixelbytesize = w * h * _bitsperpixel / 8;
//     int _filesize = _pixelbytesize + sizeof(bitmap_header_t);
//     memcpy((char *)pbitmap->fileheader.signature, "BM", 2);
//     pbitmap->fileheader.filesize = _filesize;
//     pbitmap->fileheader.fileoffset_to_pixelarray = sizeof(bitmap_header_t);
//     pbitmap->bitmapinfoheader.dibheadersize = sizeof(Bitmapinfoheader);
//     pbitmap->bitmapinfoheader.width = w;
//     pbitmap->bitmapinfoheader.height = h;
//     pbitmap->bitmapinfoheader.planes = _planes;
//     pbitmap->bitmapinfoheader.bitsperpixel = _bitsperpixel;
//     pbitmap->bitmapinfoheader.compression = _compression;
//     pbitmap->bitmapinfoheader.imagesize = _pixelbytesize;
//     pbitmap->bitmapinfoheader.ypixelpermeter = _ypixelpermeter;
//     pbitmap->bitmapinfoheader.xpixelpermeter = _xpixelpermeter;
//     pbitmap->bitmapinfoheader.numcolorspallette = 0;
//     return pbitmap;
// }
/*
static esp_err_t write_frame(http_context_t http_ctx)
{
    http_buffer_t fb_data = {
        .data = camera_get_fb(),
        .size = camera_get_data_size(),
        .data_is_persistent = true};
    return http_response_write(http_ctx, &fb_data);
}

static void handle_grayscale_pgm(http_context_t http_ctx, void *ctx)
{
    esp_err_t err = esp_camera_fb_get();
    if (err != ESP_OK)
    {
        printf("Camera capture failed with error = %d", err);
        return;
    }
    char *pgm_header_str;
    asprintf(&pgm_header_str, "P5 %d %d %d\n",
             camera_get_fb_width(), camera_get_fb_height(), 255);
    if (pgm_header_str == NULL)
    {
        return;
    }

    size_t response_size = strlen(pgm_header_str) + camera_get_data_size();
    http_response_begin(http_ctx, 200, "image/x-portable-graymap", response_size);
    http_response_set_header(http_ctx, "Content-disposition", "inline; filename=capture.pgm");
    http_buffer_t pgm_header = {.data = pgm_header_str};
    http_response_write(http_ctx, &pgm_header);
    free(pgm_header_str);

    write_frame(http_ctx);
    http_response_end(http_ctx);
    printf("Free heap: %u", xPortGetFreeHeapSize());
#if CONFIG_QR_RECOGNIZE
    camera_config_t *camera_config = ctx;
    xTaskCreate(qr_recoginze, "qr_recoginze", 111500, camera_config, 5, NULL);
#endif
}

static void handle_rgb_bmp(http_context_t http_ctx, void *ctx)
{
    esp_err_t err = esp_camera_fb_get();
    if (err != ESP_OK)
    {
        printf("Camera capture failed with error = %d", err);
        return;
    }

    bitmap_header_t *header = bmp_create_header(camera_get_fb_width(), camera_get_fb_height());
    if (header == NULL)
    {
        return;
    }

    http_response_begin(http_ctx, 200, "image/bmp", sizeof(*header) + camera_get_data_size());
    http_buffer_t bmp_header = {
        .data = header,
        .size = sizeof(*header)};
    http_response_set_header(http_ctx, "Content-disposition", "inline; filename=capture.bmp");
    http_response_write(http_ctx, &bmp_header);
    free(header);

    write_frame(http_ctx);
    http_response_end(http_ctx);
}

static void handle_jpg(http_context_t http_ctx, void *ctx)
{
    esp_err_t err = esp_camera_fb_get();
    if (err != ESP_OK)
    {
        printf("Camera capture failed with error = %d", err);
        return;
    }

    http_response_begin(http_ctx, 200, "image/jpeg", camera_get_data_size());
    http_response_set_header(http_ctx, "Content-disposition", "inline; filename=capture.jpg");
    write_frame(http_ctx);
    http_response_end(http_ctx);
}

static void handle_rgb_bmp_stream(http_context_t http_ctx, void *ctx)
{
    http_response_begin(http_ctx, 200, STREAM_CONTENT_TYPE, HTTP_RESPONSE_SIZE_UNKNOWN);
    bitmap_header_t *header = bmp_create_header(camera_get_fb_width(), camera_get_fb_height());
    if (header == NULL)
    {
        return;
    }
    http_buffer_t bmp_header = {
        .data = header,
        .size = sizeof(*header)};

    while (true)
    {
        esp_err_t err = esp_camera_fb_get();
        if (err != ESP_OK)
        {
            printf("Camera capture failed with error = %d", err);
            return;
        }

        err = http_response_begin_multipart(http_ctx, "image/bitmap",
                                            camera_get_data_size() + sizeof(*header));
        if (err != ESP_OK)
        {
            break;
        }
        err = http_response_write(http_ctx, &bmp_header);
        if (err != ESP_OK)
        {
            break;
        }
        err = write_frame(http_ctx);
        if (err != ESP_OK)
        {
            break;
        }
        err = http_response_end_multipart(http_ctx, STREAM_BOUNDARY);
        if (err != ESP_OK)
        {
            break;
        }
    }

    free(header);
    http_response_end(http_ctx);
}

static void handle_jpg_stream(http_context_t http_ctx, void *ctx)
{
    http_response_begin(http_ctx, 200, STREAM_CONTENT_TYPE, HTTP_RESPONSE_SIZE_UNKNOWN);
    while (true)
    {
        esp_err_t err = esp_camera_fb_get();
        if (err != ESP_OK)
        {
            printf("Camera capture failed with error = %d", err);
            return;
        }
        err = http_response_begin_multipart(http_ctx, "image/jpg",
                                            camera_get_data_size());
        if (err != ESP_OK)
        {
            break;
        }
        err = write_frame(http_ctx);
        if (err != ESP_OK)
        {
            break;
        }
        err = http_response_end_multipart(http_ctx, STREAM_BOUNDARY);
        if (err != ESP_OK)
        {
            break;
        }
    }
    http_response_end(http_ctx);
}

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch (event->event_id)
    {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(s_wifi_event_group, CONNECTED_BIT);
        //s_ip_addr = event->event_info.got_ip.ip_info.ip;
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        esp_wifi_connect();
        xEventGroupClearBits(s_wifi_event_group, CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}
*/
namespace Hal
{

Camera::Camera(Gpio *IoPins)
{
    // Implement assert and check in here
    esp_err_t err = nvs_flash_init();
    if (err != ESP_OK)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    _cameraConfig.ledc_channel = LEDC_CHANNEL_0;
    _cameraConfig.ledc_timer = LEDC_TIMER_0;
    _cameraConfig.pin_d0 = 5;
    _cameraConfig.pin_d1 = 18;
    _cameraConfig.pin_d2 = 19;
    _cameraConfig.pin_d3 = 21;
    _cameraConfig.pin_d4 = 36;
    _cameraConfig.pin_d5 = 39;
    _cameraConfig.pin_d6 = 34;
    _cameraConfig.pin_d7 = 35;
    _cameraConfig.pin_xclk = 0;
    _cameraConfig.pin_pclk = 22;
    _cameraConfig.pin_vsync = 25;
    _cameraConfig.pin_href = 23;
    _cameraConfig.pin_sscb_sda = 26;
    _cameraConfig.pin_sscb_scl = 27;
    _cameraConfig.pin_reset = -1;
    _cameraConfig.pin_pwdn = 32;
    _cameraConfig.xclk_freq_hz = 10000000;
    _cameraConfig.jpeg_quality = 10;
    _cameraConfig.fb_count = 1;
    _cameraConfig.frame_size = static_cast<framesize_t>(CameraFrameSize::CameraFrameSizeVGA);
    _cameraConfig.pixel_format = static_cast<pixformat_t>(CameraPixelFormat::CameraPixelFormatJPEG);
}

const camera_fb_t *Camera::GetFrameBuffer()
{
    return _frameBuffer;
}

bool Camera::Capture()
{
    _frameBuffer = esp_camera_fb_get();
    if (_frameBuffer == nullptr)
    {
        printf("Camera capture failed\n");
        return false;
    }
    return true;
}

void Camera::DeInit()
{
    esp_camera_deinit();
}

void Camera::SetResolution(CameraFrameSize frameSize)
{
    _cameraConfig.frame_size = static_cast<framesize_t>(frameSize);
}

void Camera::SetImageFormat(CameraPixelFormat format)
{
    _cameraConfig.pixel_format = static_cast<pixformat_t>(format);
}

void Camera::Init()
{

    // esp_err_t err = camera_probe((camera_config_t *)&cameraConfig, (camera_model_t *)(&cameraConfig.CameraModel));
    // if (err != ESP_OK)
    // {
    //     printf("Camera probe failed with error 0x%x\n", err);
    //     return;
    // }

    // if (cameraConfig.CameraModel == CameraModelType::CameraOV7725)
    // {
    //     printf("Detected OV7725 camera, using %s bitmap format",
    //            cameraConfig.PixelFormat == CAMERA_PF_GRAYSCALE ? "grayscale" : "RGB565");
    // }
    // else if (cameraConfig.CameraModel == CameraModelType::CameraOV2640)
    // {
    //     printf("Detected OV2640 camera, using JPEG format");
    //     if (cameraConfig.PixelFormat == (camera_framesize_t) CameraPixelFormat::CameraPixelFormatJPEG)
    //         cameraConfig.JPEGQuality = 5;
    // }
    // else
    // {
    //     printf("Camera not supported");
    //     return;
    // }

    esp_err_t err = esp_camera_init((camera_config_t *)&_cameraConfig);
    if (err != ESP_OK)
    {
        printf("Camera init failed with error 0x%x", err);
        return;
    }

    // s_wifi_event_group = xEventGroupCreate();

    // printf("Connected\n");

    // http_server_t server;
    // http_server_options_t http_options = HTTP_SERVER_OPTIONS_DEFAULT();
    // ESP_ERROR_CHECK(http_server_start(&http_options, &server));

    // if (s_pixel_format == CAMERA_PF_GRAYSCALE)
    // {
    //     ESP_ERROR_CHECK(http_register_handler(server, "/pgm", HTTP_GET, HTTP_HANDLE_RESPONSE, &handle_grayscale_pgm, &camera_config));
    //     printf("Open http:// %d.%d.%d.%d /pgm for a single image/x-portable-graymap image\n", IP2STR(&s_ip_addr));
    // }
    // if (s_pixel_format == CAMERA_PF_RGB565)
    // {
    //     ESP_ERROR_CHECK(http_register_handler(server, "/bmp", HTTP_GET, HTTP_HANDLE_RESPONSE, &handle_rgb_bmp, NULL));
    //     printf("Open http://%d.%d.%d.%d/bmp for single image/bitmap image\n", IP2STR(&s_ip_addr));
    //     ESP_ERROR_CHECK(http_register_handler(server, "/bmp_stream", HTTP_GET, HTTP_HANDLE_RESPONSE, &handle_rgb_bmp_stream, NULL));
    //     printf("Open http://%d.%d.%d.%d/bmp_stream for multipart/x-mixed-replace stream of bitmaps\n", IP2STR(&s_ip_addr));
    // }
    // if (s_pixel_format == CAMERA_PF_JPEG)
    // {
    //     ESP_ERROR_CHECK(http_register_handler(server, "/jpg", HTTP_GET, HTTP_HANDLE_RESPONSE, &handle_jpg, NULL));
    //     printf("Open http://%d.%d.%d.%d/jpg for single image/jpg image\n", IP2STR(&s_ip_addr));
    //     ESP_ERROR_CHECK(http_register_handler(server, "/jpg_stream", HTTP_GET, HTTP_HANDLE_RESPONSE, &handle_jpg_stream, NULL));
    //     printf("Open http://%d.%d.%d.%d/jpg_stream for multipart/x-mixed-replace stream of JPEGs\n", IP2STR(&s_ip_addr));
    // }
    // printf("Free heap: %u\n", xPortGetFreeHeapSize());
    // printf("Camera demo ready\n");
}

Camera::~Camera()
{
}

} // namespace Hal
