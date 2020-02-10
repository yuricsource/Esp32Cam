const { ipcRenderer } = window.require("electron");

const updateItem = ({ id, label }) => {
  ipcRenderer.send("menu-update", { id, label });
};

export default {
  updateItem
};
