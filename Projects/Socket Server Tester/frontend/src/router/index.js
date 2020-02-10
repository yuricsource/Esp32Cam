import Vue from "vue";
import Router from "vue-router";

import InitialModule from "@/modules/initial-module.vue";
// import WebServerModule from "@/modules/web-server-module.vue";

Vue.use(Router);

const router = new Router({
  linkActiveClass: "active",
  routes: [
    {
      path: "/",
      name: "DashboardModule",
      component: InitialModule
    }
    // {
    //   path: "/",
    //   name: "DashboardModule",
    //   component: WebServerModule
    // }
    // {
    //   path: "/config",
    //   name: "ConfigModule",
    //   component: ConfigModule
    // }
  ]
});

export default router;
