import { createApp } from 'vue'
import { createRouter, createWebHashHistory } from "vue-router";
import main_routes from "./routes";
import main_app from "./app";
import "bootstrap";
import "bootstrap/dist/css/bootstrap.min.css";

const router = createRouter({ history: createWebHashHistory(), routes: main_routes });

const app = createApp(main_app);
app.use(router).mount("#app");