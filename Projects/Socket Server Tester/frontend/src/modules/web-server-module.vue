<template>
  <div class="web-server-module">
    <div>
      local webserver
      <div :type="status !== 'running' ? 'secondary' : 'success'">
        {{ status }}
      </div>
    </div>

    <div slot="menu">
      <div class="col-xs-12 text-right">
        <button @click="open" :disabled="status !== 'running'">
          Open Chrome
        </button>
        <button @click="toggle">{{ btnToggle }}</button>
      </div>
    </div>

    <div class="web-server-module__body">
      <div class="web-server-module__get-folder col-xs-12 col-sm-6 col-md-2">
        {{ folder }} <br />
        <div class="btn btn-primary web-server-module__get-folder__button">
          Select Folder
        </div>
        <input
          class="web-server-module__get-folder__input"
          type="file"
          @click="getFolder"
          webkitdirectory
        />
      </div>

      <div>
        <input v-model="port" />
      </div>
    </div>
  </div>
</template>

<script>
import exec from "@/core/exec";
import server from "@/core/server";
// import { mapState, mapActions } from "vuex";

export default {
  name: "web-server-module",
  components: {},
  data() {
    return {
      // logs: '',
      status: "stopped",
      btnToggle: "Start",
      instance: null,
      folder: null,
      port: 3000,
    };
  },
  methods: {
    getFolder(evt) {
      const { target } = evt;

      // const folder = (target.files.length > 0) ? `${target.files[0].path}/${target.files[0].name}` : '...';
      const folder = target.files.length > 0 ? target.files[0].path : "..."; // TODO: bit buggy... needs improvement
      // console.log('getFolder', evt);
      // console.log('getFolder', target.files);
      // console.log('getFolder', folder);
      this.setFolder(folder);
    },
    open() {
      exec(`open -a "Google Chrome" http://localhost:${this.port}/`); // .catch(consoleLog);
    },
    toggle() {
      if (this.instance) {
        this.btnToggle = "Stopping...";
        this.status = "stopping...";
        this.instance.close(() => {
          this.instance = null;
          this.btnToggle = "Start";
          this.status = "stopped";
        });
        return true;
      }

      this.btnToggle = "Starting...";
      this.status = "starting...";
      this.instance = server({
        port: this.port,
        folder: this.folder,
        onStart: () => {
          this.btnToggle = "Stop";
          this.status = "running";
        }
        // onLog: (string)=> this.logsUpdate(string), // TODO: implement
      });
      this.open();
    }
    // logsUpdate(string) {
    //   this.logs = `${string}\n${this.logs}`;
    // },
    // ...mapActions("Webserver", ["setFolder", "setPort"])
  },
  computed: {
    // ...mapState("Webserver", ["folder", "port"])
  }
};
</script>

<style scoped>
.web-server-module {
}

.web-server-module__get-folder {
  position: relative;
}

.web-server-module__get-folder__button {
  position: absolute;
  left: 0;
  right: 0;
  cursor: pointer;
}

.web-server-module__get-folder__input {
  opacity: 0;
  position: absolute;
  left: 0;
  right: 0;
  width: 100%;
  height: 100%;
  z-index: 2;
  cursor: pointer;
}

.web-server-module__body {
  display: flex;
  padding: 10px;
  flex-direction: column;
}
</style>
