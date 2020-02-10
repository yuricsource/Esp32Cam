import Vue from "vue";
import Vuex from "vuex";

Vue.use(Vuex);

import { get, set, del } from "./storage";
import menu from "@/core/menu";

const storeKey = "__config__";

const defaults = {
  // shellPath: PATH,
  shellPathCustom: "",
  dockerComposePath: "/usr/local/bin/docker-compose",
  dockerPath: "/usr/local/bin/docker",
  awsPath: "/Library/Frameworks/Python.framework/Versions/3.7/bin/aws",
  awsKeyDate: null,
  view: null,
  myModules: [],
  frontend: {
    npm: null,
    nvm: null,
    node: null
  }
};

const state = Object.assign({}, defaults, get(storeKey));
if (state.awsKeyDate) {
  state.awsKeyDate = new Date(state.awsKeyDate);
}

// console.log('STATE', state);

const store = new Vuex.Store({
  plugins: [],
  modules: {},
  strict: process.env.NODE_ENV !== "production",
  state,
  getters: {
    shellPath(state) {
      return `${state.shellPath}${state.shellPathCustom}`;
    }
  },

  mutations: {
    setFrontend(state, payload) {
      state.frontend = { ...state.frontend, ...payload };
    },
    setMyModule(state, { module, action }) {
      if (action === "add") {
        state.myModules.push(module);
        return true;
      }

      state.myModules.splice(state.myModules.indexOf(module), 1);
    },
    setShellPathCustom(state, payload) {
      state.shellPathCustom = payload;
    },
    setDockerPath(state, payload) {
      state.dockerPath = payload;
    },
    setDockerComposePath(state, payload) {
      state.dockerComposePath = payload;
    },
    setAwsPath(state, payload) {
      state.awsPath = payload;
    },
    setView(state, payload) {
      if (payload === "DNS") {
        state.myModules = ["dns"];
      } else {
        state.myModules = ["dns", "devbox", "webapp", "webserver", "hr"];
      }

      state.view = payload;
    },
    setAwsKeyDate(state, date) {
      state.awsKeyDate = date || new Date();
    },
    storageSave(state) {
      set(storeKey, state);
    },
    resetConfig() {
      del(storeKey);
    }
  },

  actions: {
    setFrontend({ commit }, payload) {
      commit("setFrontend", payload);
      commit("storageSave");
    },
    resetConfig({ commit }) {
      commit("resetConfig");
    },
    setMyModule({ commit }, payload) {
      commit("setMyModule", payload);
      commit("storageSave");
    },
    setShellPathCustom({ commit }, payload) {
      commit("setShellPathCustom", payload);
      commit("storageSave");
    },
    setDockerPath({ commit }, payload) {
      commit("setDockerPath", payload);
      commit("storageSave");
    },
    setDockerComposePath({ commit }, payload) {
      commit("setDockerComposePath", payload);
      commit("storageSave");
    },
    setAwsPath({ commit }, payload) {
      commit("setAwsPath", payload);
      commit("storageSave");
    },
    setView({ commit }, payload) {
      commit("setView", payload);
      commit("storageSave");
    },
    // eslint-disable-next-line no-unused-vars
    setMenu({ commit }, payload) {
      // commit('setMenu', payload);
      menu.updateItem(payload);
    },
  }
});

export default store;
