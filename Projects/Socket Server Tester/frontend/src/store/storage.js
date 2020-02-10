const storeDefault = "__config__";

const del = store => {
  delete localStorage[store];
};

const get = store => {
  let dataStored = {};
  try {
    dataStored = JSON.parse(localStorage.getItem(store || storeDefault));
  } catch (e) {
    dataStored = {};
  }

  return dataStored;
};

const set = (store, data = {}) => {
  let dataToStore = {};
  try {
    dataToStore = JSON.stringify(data);
  } catch (e) {
    dataToStore = JSON.stringify({});
  }

  localStorage.setItem(store || storeDefault, dataToStore);
};

export { get, set, del };
