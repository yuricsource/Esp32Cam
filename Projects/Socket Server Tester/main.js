// Modules to control application life and create native browser window

const {app, BrowserWindow, Tray, Menu, ipcMain, nativeImage} = require('electron');

// Keep a global reference of the window object, if you don't, the window will
// be closed automatically when the JavaScript object is garbage collected.
let mainWindow;
let tray;
let trayMenu;

function createWindow() {
  // Create the browser window.
  mainWindow = new BrowserWindow({
    width: (process.env.NODE_ENV === 'development') ? 900 : 300,
    height: (process.env.NODE_ENV === 'development') ? 900 : 300,
    // minWidth: 800,
    // maxWidth: 800,
    // minHeight: 600,
    // maxHeight: 600,
    // frame: false,
    // zoomToPageWidth: true,
    // transparent: true,
    // titleBarStyle: 'hiddenInset',
    // vibrancy: 'dark',
    // tabbingIdentifier: '',
    // show: false,
    // backgroundColor: '#111',
    titleBarStyle: 'hidden-inset',
    webPreferences: {
      zoomFactor: 1,
      allowRunningInsecureContent: false,
      webgl: false,
      webaudio: false,
      // offscreen: true,
    },
  });

  if (process.env.NODE_ENV === 'development') {
    mainWindow.openDevTools();
  }

  const socket = require('./app/socket');
  socket.create();
  mainWindow.loadURL('http://localhost:3333');

  // Open the DevTools.
  // mainWindow.openDevTools();
  // mainWindow.webContents.openDevTools()

  // Emitted when the window is closed.
  mainWindow.on('closed', function(event, a) {
  //   event.preventDefault();
    console.log('closed');
    mainWindow = null;
  //   // Dereference the window object, usually you would store windows
  //   // in an array if your app supports multi windows, this is the time
  //   // when you should delete the corresponding element.
  //   // mainWindow = null;

  //   // console.log('mainWindow.on close', e, a);
  //   // if (!application.isQuiting) {
  //   //   event.preventDefault();
  //   //   return mainWindow.hide();
  //   // }

  //   // mainWindow = null;
  //   mainWindow.hide();
  });

  mainWindow.on('close', function(event, a) {
    // event.preventDefault();
    // mainWindow.hide();
    console.log('close', event, a);
  });

  // mainWindow.onbeforeunload = (event) => {
  //   event.returnValue = false;
  //   mainWindow.hide();
  // };

  mainWindow.on('minimize', (event) => {
    event.preventDefault();
    mainWindow.hide();
  });

  // if (!tray) {
  //   const path = require('path');
  //   const platform = require('os').platform();
  //   const iconTrayImagePath = path.resolve(__dirname, 'build', platform, 'icon-tray.png');
  //   console.log('################');
  //   console.log(iconTrayImagePath);
  //   console.log('################');
  //   const iconTrayImage = nativeImage.createFromPath(iconTrayImagePath);
  //   iconTrayImage.setTemplateImage(true);
  //
  //   createTray(iconTrayImagePath);
  // }

  if (process.env.NODE_ENV !== 'development') {
    const template = [
      {
        label: 'Application',
        submenu: [
          {label: 'About Application', selector: 'orderFrontStandardAboutPanel:'},
          {type: 'separator'},
          {label: 'Quit', accelerator: 'Command+Q', role: 'quit'},
        ],
      },
      {
        label: 'Edit',
        submenu: [
          {label: 'Undo', accelerator: 'CmdOrCtrl+Z', selector: 'undo:'},
          {label: 'Redo', accelerator: 'Shift+CmdOrCtrl+Z', selector: 'redo:'},
          {type: 'separator'},
          {label: 'Cut', accelerator: 'CmdOrCtrl+X', selector: 'cut:'},
          {label: 'Copy', accelerator: 'CmdOrCtrl+C', selector: 'copy:'},
          {label: 'Paste', accelerator: 'CmdOrCtrl+V', selector: 'paste:'},
          {label: 'Select All', accelerator: 'CmdOrCtrl+A', selector: 'selectAll:'},
        ],
      },
    ];

    Menu.setApplicationMenu(Menu.buildFromTemplate(template));
  }
}

// TODO: known bug will crash the app if try to update the menu 2x at same time
const menuUpdate = ({id, label}) => {
  // console.log('menuUpdate', trayMenu);
  // console.log('menuUpdate', id, label);
  const menuItem = trayMenu.getMenuItemById(id);
  // console.log('menuUpdate', menuItem);
  menuItem.label = label;
  // console.log('menuUpdate', menuItem);
  trayMenu = Menu.buildFromTemplate(trayMenu.items);
  // contextMenu.items[1].label = new Date().toLocaleString();
  tray.setContextMenu(trayMenu);
};

ipcMain.on('menu-update', (evt, data) => menuUpdate(data));

const createTray = (iconTrayImagePath) => {
  tray = new Tray(iconTrayImagePath);
  tray.setPressedImage(iconTrayImagePath);
  trayMenu = Menu.buildFromTemplate([
    {label: 'Dns: loading...', id: 'dns'},
    {label: 'Devbox: not installed', id: 'devbox'},
    {label: 'Webapp: not installed', id: 'webapp'},
    {label: 'HR: not installed', id: 'hr'},
    {label: 'Svc URL: not installed', id: 'svc-url'},
    {type: 'separator'},
    // {
    //   label: 'Open',
    //   id: 'open',
    //   click: () => mainWindow.show(),
    // },
    // {
    //   label: 'Change interface',
    //   id: 'changeInterface',
    //   click: () => mainWindow.show(),
    // },
    // {
    //   label: 'Hide',
    //   id: 'hide',
    //   click: () => mainWindow.hide(),
    // },
    {
      label: 'Restart network',
      id: 'network',
      click: () => card.restart(),
    },
    // {label: 'Item3', type: 'radio', checked: true},
    {label: 'Quit', role: 'quit'},
  ]);
  tray.setToolTip('This is my application.');
  tray.setContextMenu(trayMenu);

  // tray.on('click', () => {
  //   mainWindow.isVisible() ? mainWindow.hide() : mainWindow.show();
  // });
  // mainWindow.on('show', () => {
  //   tray.setHighlightMode('always');
  // });
  // mainWindow.on('hide', () => {
  //   tray.setHighlightMode('never');
  // });
};

// app.on('updateMenu', updateMenu);

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.on('ready', createWindow);
// app.on('browser-window-created', createTray);

// Quit when all windows are closed.
app.on('window-all-closed', function() {
  // On OS X it is common for applications and their menu bar
  // to stay active until the user quits explicitly with Cmd + Q
  if (process.platform !== 'darwin') {
    app.quit();
  } else {
    mainWindow.hide();
  }
});

app.on('activate', function(evt) {
  // On OS X it's common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  if (mainWindow === null) {
    createWindow();
  } else {
    mainWindow.show();
  }
});


// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and require them here.


// const os = require('os');
// console.log('#### ', os.networkInterfaces());
