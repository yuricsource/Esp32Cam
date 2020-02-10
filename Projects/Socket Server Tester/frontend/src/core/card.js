import exec from "./exec";
// const {networkInterfaces} = require('os');
const os = require("os");
window.os = os;
// os.networkInterfaces()
// const defaultCard = "en0";
const defaultCard = "Wi-Fi";

let on = (card = defaultCard) =>
  exec(`networksetup -setairportpower ${card} on`);

let off = (card = defaultCard) =>
  exec(`networksetup -setairportpower ${card} off`);

// let list = () => os.networkInterfaces();
let list = async () => {
  try {
    const list = await exec(`networksetup -listallnetworkservices`);
    return list
      .split("\n")
      .filter(item => !!item)
      .splice(1, list.length);
  } catch (e) {
    console.error(e);
    throw e;
  }
};

let restart = async (card = defaultCard) => {
  try {
    await off(card);
    await new Promise(r => setTimeout(r, 1000));
    await on(card);
  } catch (e) {
    console.error(e);
    throw e;
  }

  return true;
};

export async function testInternetConnection() {
  // if (time) {
  //   exec({command: 'ping -t 2 google.com', pipe: ({data, type})=> {
  //       console.log(type, '**', data);
  //     }});
  // }

  try {
    if (
      (
        await exec(`curl --max-time 4 www.google.com > /dev/null; echo $?`)
      ).trim() === "0"
    ) {
      return true;
    }
  } catch (e) {
    console.error(e);
  }

  return false;
}

export async function setDns(dns, card = defaultCard) {
  return exec(`networksetup -setdnsservers ${card} ${dns}`);
}

export async function getDns(card = defaultCard) {
  return exec(`networksetup -getdnsservers ${card}`).then(dns => dns.trim());
}

export async function isLocalHost(card = defaultCard) {
  return getDns(card).then(dns => dns.indexOf('127.0.0.1') > -1);
}

window.card = {
  restart,
  on,
  off,
  list,
  testInternetConnection,
  getDns,
  setDns,
  isLocalHost
};
export default {
  restart,
  on,
  off,
  list,
  testInternetConnection,
  getDns,
  setDns,
  isLocalHost
};
