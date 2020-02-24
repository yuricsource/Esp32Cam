
#include "Tests.h"
#include "esp_http_server.h"

using Hal::Dwt;
using Hal::Hardware;
using Hal::TimeLimit;

using namespace std;

const char *testPhrase = "RTC holds the memory with low power";

#define PART_BOUNDARY "123456789000000000000987654321"
static const char *_STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char *_STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char *_STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";
httpd_handle_t stream_httpd = NULL;

static esp_err_t stream_handler(httpd_req_t *req)
{
	camera_fb_t *fb = NULL;
	esp_err_t res = ESP_OK;
	size_t _jpg_buf_len = 0;
	uint8_t *_jpg_buf = NULL;
	char *part_buf[64];
	//dl_matrix3du_t *image_matrix = NULL;
	// bool detected = false;
	// int face_id = 0;
	// int64_t fr_start = 0;
	// int64_t fr_ready = 0;
	// int64_t fr_face = 0;
	// int64_t fr_recognize = 0;
	// int64_t fr_encode = 0;

	static int64_t last_frame = 0;
	if (!last_frame)
	{
		last_frame = esp_timer_get_time();
	}

	res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
	if (res != ESP_OK)
	{
		return res;
	}

	httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");

	while (true)
	{
		// detected = false;
		// face_id = 0;
		fb = esp_camera_fb_get();
		if (!fb)
		{
			printf("Camera capture failed");
			res = ESP_FAIL;
		}
		else
		{
			// fr_start = esp_timer_get_time();
			// fr_ready = fr_start;
			// fr_face = fr_start;
			// fr_encode = fr_start;
			// fr_recognize = fr_start;

			if (fb->format != PIXFORMAT_JPEG)
			{
				bool jpeg_converted = frame2jpg(fb, 80, &_jpg_buf, &_jpg_buf_len);
				esp_camera_fb_return(fb);
				fb = NULL;
				if (!jpeg_converted)
				{
					printf("JPEG compression failed");
					res = ESP_FAIL;
				}
			}
			else
			{
				_jpg_buf_len = fb->len;
				_jpg_buf = fb->buf;
			}
		}
		if (res == ESP_OK)
		{
			size_t hlen = snprintf((char *)part_buf, 64, _STREAM_PART, _jpg_buf_len);
			res = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
		}
		if (res == ESP_OK)
		{
			res = httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
		}
		if (res == ESP_OK)
		{
			res = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY));
		}
		if (fb)
		{
			esp_camera_fb_return(fb);
			fb = NULL;
			_jpg_buf = NULL;
		}
		else if (_jpg_buf)
		{
			free(_jpg_buf);
			_jpg_buf = NULL;
		}
		if (res != ESP_OK)
		{
			break;
		}
		// int64_t fr_end = esp_timer_get_time();
	}

	last_frame = 0;
	return res;
}

const char *GetTestPhrase()
{
	return testPhrase;
}

void TestSdCard()
{
	Hardware *system = Hal::Hardware::Instance();
	if (system->GetSdCard().Mount())
	{
		printf("Opening file\n");
		FILE *f = fopen("/sdcard/hello.txt", "w");
		if (f == NULL)
		{
			printf("Failed to open file for writing\n");
			return;
		}
		fprintf(f, "Hello, how are you?\n");
		fclose(f);
		printf("File written\n");

		// Check if destination file exists before renaming
		struct stat st;
		if (stat("/sdcard/foo.txt", &st) == 0)
		{
			// Delete it if it exists
			unlink("/sdcard/foo.txt");
		}

		// Rename original file
		printf("Renaming file\n");
		if (rename("/sdcard/hello.txt", "/sdcard/foo.txt") != 0)
		{
			printf("Rename failed\n");
			return;
		}

		// Open renamed file for reading
		printf("Reading file\n");
		f = fopen("/sdcard/foo.txt", "r");
		if (f == nullptr)
		{
			printf("Failed to open file for reading\n");
			return;
		}
		char line[64];
		fgets(line, sizeof(line), f);
		fclose(f);
		// strip newline
		char *pos = strchr(line, '\n');
		if (pos)
			*pos = '\0';
		printf("Read from file: '%s'", line);
	}
	else
		printf("Error: SdCard not mounted.\n");
}

void TestSpiffs()
{
	if (Hardware::Instance()->GetSpiffs().IsMounted() == false)
	{
		if (Hardware::Instance()->GetSpiffs().Mount() == false)
		{
			printf("\n\nSPIFFS failed!\n\n");
			return;
		}
	}

	printf("\n\nOpening file\n");
	FILE *f = fopen("/spiffs/hello.txt", "w");
	if (f == NULL)
	{
		printf("Failed to open file for writing");
		return;
	}
	fprintf(f, "SPIFFS is Working!!! Hooray!!! :D\n");
	fclose(f);
	printf("File written\n");

	// Check if destination file exists before renaming
	struct stat st;
	if (stat("/spiffs/foo.txt", &st) == 0)
	{
		// Delete it if it exists
		unlink("/spiffs/foo.txt");
	}

	// Rename original file
	printf("Renaming file\n");
	if (rename("/spiffs/hello.txt", "/spiffs/foo.txt") != 0)
	{
		printf("Rename failed\n");
		return;
	}

	printf("Reading Test file\n");
	f = fopen("/spiffs/lala.txt", "r");
	if (f == NULL)
	{
		printf("Failed to open file for reading\n");
		return;
	}

	char line[64];
	fgets(line, sizeof(line), f);
	fclose(f);

	// Open renamed file for reading
	printf("Reading Stored Test file\n");
	f = fopen("/spiffs/lala.txt", "r");
	if (f == NULL)
	{
		printf("Failed to open file for reading\n");
		return;
	}

	fgets(line, sizeof(line), f);
	fclose(f);
	// strip newline
	char *pos = strchr(line, '\n');
	if (pos)
	{
		*pos = '\0';
	}

	printf("Read from file: '%s'\n\n", line);
}

void PutCpuToSleep()
{
	printf("\n\nI'm going to bed and I will be back in 5 seconds. BYE :)\n\n");

	Hardware::Instance()->DeepSleep(5 * 1000 * 1000);
}

void SoftwareResetTest()
{
	Hardware::Instance()->SoftwareReset();
}

char ReadKey()
{
	char key = 0;
	while (key == 0)
	{
		scanf("%c", &key);
		vTaskDelay(5);
	}
	return key;
}

void ReadString(char *string, uint8_t size)
{
	uint8_t i = 0;
	char key = 0;
	while (true)
	{
		vTaskDelay(1);
		scanf("%c", &key);
		if (key == 10) // [Enter]
		{
			string[i] = '\0';
			break;
		}
		else if (key == 8) // [Backspace]
		{
			printf("%c %c", 8, 8); // clean the previous char
			i--;
			key = 0;
		}
		else if (key != 0)
		{
			string[i] = key;
			printf("%c", key);
			i++;
			key = 0;
			if (i == size - 1) // if the last key has reached the end of the buffer
			{
				string[i + 1] = '\0';
				break;
			}
		}
	}
	printf("\n");
}

void WifiMenu()
{
	char test = 0;

	while (1)
	{
		switch (test)
		{
		case 's':
		case 'S':
		{
			char mode = 0;
			printf("\n\nSet the Wifi mode:\n\n");
			printf("[1] - Client\n");
			printf("[2] - Hotspot\n");
			printf("[3] - Mesh Network\n");
			mode = ReadKey();
			if (mode == '1')
			{
				Hardware::Instance()->GetWifi().SetMode(Hal::WifiModeConfiguration::Client);
				printf("Configured as Wifi Client.\n");
			}
			else if (mode == '2')
			{
				Hardware::Instance()->GetWifi().SetMode(Hal::WifiModeConfiguration::HotSpot);
				printf("Configured as HotSpot.\n");
			}
			else if (mode == '3')
			{
				Hardware::Instance()->GetWifi().SetMode(Hal::WifiModeConfiguration::Mesh);
				printf("Configured as Mesh network (not supported yet).\n");
			}
			else
				printf("Invalid option.\n");
		}
		break;
		case 'i':
		case 'I':
		{
			char ssid[Hal::WifiSsidMaxLength] = {};
			test = 0;
			printf("Enter the SSID:\n");
			ReadString(ssid, Hal::WifiSsidMaxLength);
			printf("\nSSID set to \"%s\"\n", ssid);
			scanf("%s", ssid);
			Hardware::Instance()->GetWifi().SetSsid(ssid, strlen(ssid));
		}
		break;
		case 'p':
		case 'P':
		{
			char passwd[Hal::WifiPasswordMaxLength] = {};
			printf("Enter the Password:\n");
			ReadString(passwd, Hal::WifiPasswordMaxLength);
			printf("\nPassword set to \"%s\"\n", passwd);
			Hardware::Instance()->GetWifi().SetPassword(passwd, strlen(passwd));
		}
		break;
		case 'c':
		case 'C':
		{
			char channel = 0;
			printf("Enter the channel: \n");
			channel = ReadKey();
			channel -= 48;
			printf("%d", channel);
			Hardware::Instance()->GetWifi().SetChannel(channel);
		}
		break;
		case 't':
		case 'T':
		{
			Hardware::Instance()->GetWifi().Enable();
		}
		break;
		case 'z':
		case 'Z':
		{
			Hardware::Instance()->GetWifi().Disable();
		}
		break;
		case 'x':
		case 'X':
		{
			return;
		}
		break;
		default:
			break;
		}

		printf("\n");
		printf("Wifi menu:\n");
		printf("----------\n");
		printf("[S] - Set WiFi Mode (AP, STA or Mesh)\n");
		printf("[I] - Set WiFi SSID\n");
		printf("[P] - Set WiFi Password\n");
		printf("[C] - Set WiFi Channel\n");
		printf("[T] - Start Wifi\n");
		printf("[Z] - Stop Wifi\n");
		printf("[X] - Return\n");

		test = ReadKey();
	}
}

void LedMenu()
{
	char test = 0;

	while (1)
	{
		switch (test)
		{
		case 'q':
		case 'Q':
		{
			Hardware::Instance()->GetLeds().SetLed(Hal::Leds::LedIndex::FlashLed);
		}
		break;
		case 'a':
		case 'A':
		{
			Hardware::Instance()->GetLeds().ResetLed(Hal::Leds::LedIndex::FlashLed);
		}
		break;
		case 'w':
		case 'W':
		{
			Hardware::Instance()->GetLeds().SetLed(Hal::Leds::LedIndex::RedLed);
		}
		break;
		case 's':
		case 'S':
		{
			Hardware::Instance()->GetLeds().ResetLed(Hal::Leds::LedIndex::RedLed);
		}
		break;
		case 'x':
		case 'X':
		{
			return;
		}
		break;
		default:
			break;
		}

		printf("\n");
		printf("Led menu:\n");
		printf("----------\n");
		printf("[Q] - Turn Flash On\n");
		printf("[A] - Turn Flash Off\n");
		printf("[W] - Turn Red Led On\n");
		printf("[S] - Turn Red Led Off\n");
		printf("[X] - Return\n");

		test = ReadKey();
	}
}

void CameraMenu()
{
	char test = 0;

	while (1)
	{
		switch (test)
		{
		case 's':
		case 'S':
		{
			char mode = 0;
			printf("\n\nSet the camera resolution:\n\n");
			printf("[0] - QQVGA\t(160x120)\n");
			printf("[1] - QVGA \t(320x240)\n");
			printf("[2] - VGA  \t(640x480)\n");
			printf("[3] - SVGA \t(800x600)\n");
			printf("[4] - SXGA \t(1280x1024)\n");
			printf("[5] - UXGA \t(1600x1200)\n");
			mode = ReadKey();
			if (mode == '0')
			{
				Hal::Hardware::Instance()->GetCamera().SetResolution(Hal::CameraFrameSize::CameraFrameSizeQQVGA);
			}
			if (mode == '1')
			{
				Hal::Hardware::Instance()->GetCamera().SetResolution(Hal::CameraFrameSize::CameraFrameSizeQVGA);
			}
			else if (mode == '2')
			{
				Hal::Hardware::Instance()->GetCamera().SetResolution(Hal::CameraFrameSize::CameraFrameSizeVGA);
			}
			else if (mode == '3')
			{
				Hal::Hardware::Instance()->GetCamera().SetResolution(Hal::CameraFrameSize::CameraFrameSizeSVGA);
			}
			else if (mode == '4')
			{
				Hal::Hardware::Instance()->GetCamera().SetResolution(Hal::CameraFrameSize::CameraFrameSizeSXGA);
			}
			else if (mode == '5')
			{
				Hal::Hardware::Instance()->GetCamera().SetResolution(Hal::CameraFrameSize::CameraFrameSizeUXGA);
			}
			else
				printf("Invalid option.\n");
		}
		break;
		case 'i':
		case 'I':
		{
			Hardware *system = Hal::Hardware::Instance();
			system->GetCamera().SetResolution(Hal::CameraFrameSize::CameraFrameSizeSVGA);
			if (system->GetSdCard().Mount())
			{
				printf("Heap Before the Camera       		: %d\n", esp_get_free_heap_size());
				Hardware::Instance()->GetCamera().Init();
				printf("Heap After the Camera       		: %d\n", esp_get_free_heap_size());
				for (uint8_t i = 0; i < 10; i++)
				{
					Hardware::Instance()->GetCamera().Capture();
					std::array<char, 30> fileName;

					snprintf(fileName.data(), fileName.size(), "/sdcard/%s%d.jpg", "pic", i + 1);
					struct stat st;
					if (stat(fileName.data(), &st) == 0)
					{
						// Delete it if it exists
						unlink(fileName.data());
					}

					printf("Opening file\n");
					FILE *f = fopen(fileName.data(), "wb");
					if (f == NULL)
					{
						printf("Failed to open file for writing\n");
						return;
					}

					const camera_fb_t *fb = Hardware::Instance()->GetCamera().GetFrameBuffer();
					if (fb != nullptr)
					{
						printf("Photo Captured, Saving in the SD Card. Image size:%d\n", fb->len);
						fwrite(fb->buf, fb->len, 1, f);
						printf("Closing file\n");
					}
					else
						printf("Frame Buffer failed\n");

					fclose(f);
				}
				Hardware::Instance()->GetCamera().DeInit();
			}
			else
				printf("Error: SdCard not mounted.\n");

			system->GetSdCard().Unmount();
		}
		break;
		case 'w':
		case 'W':
		{
			httpd_config_t config = HTTPD_DEFAULT_CONFIG();
			httpd_uri_t stream_uri =
				{
					.uri = "/stream",
					.method = HTTP_GET,
					.handler = stream_handler,
					.user_ctx = NULL};
			if (httpd_start(&stream_httpd, &config) == ESP_OK)
			{
				httpd_register_uri_handler(stream_httpd, &stream_uri);
			}
		}
		break;
		case 'x':
		case 'X':
		{
			return;
		}
		break;
		default:
			break;
		}

		printf("\n");
		printf("Camera menu:\n");
		printf("----------\n");
		printf("[S] - Camera Resolution\n");
		//printf("[P] - Capture and Save in the internal Flash\n");
		printf("[I] - Capture 10 images and Save in the SD Card\n");
		printf("[W] - Start Streaming Web\n");
		printf("[X] - Return\n");

		test = ReadKey();
	}
}