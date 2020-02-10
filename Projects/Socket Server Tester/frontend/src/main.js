import Vue from "vue";
import App from "./app.vue";
import router from "./router";
import store from "./store";

Vue.config.productionTip = false;

/* eslint-disable no-new */
window.App = new Vue({
  router,
  store,
  render: h => h(App)
}).$mount("#app");
