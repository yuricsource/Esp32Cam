<template>
  <div id="app">
    <router-view />
  </div>
</template>

<style lang="scss">
@import "./assets/font/css/all.min.css";

#app {
  width: 100%;
  height: 100%;
}

html,
body {
  background: #ddd;
  margin: 0;
  padding: 0;
  width: 100%;
  height: 100%;
}

* {
  -webkit-overflow-scrolling: touch;
  outline: none;
  box-sizing: border-box;
}

*:focus {
  outline: none !important;
}
</style>
