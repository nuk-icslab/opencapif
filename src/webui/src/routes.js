import apis from "pages/apis";
import logs from "pages/logs";
import new_api from "pages/new-api";

export default [
    {
        path: "/",
        name: "apis",
        component: apis,
    },
    {
        path: "/logs",
        name: "logs",
        component: logs,
    },
    {
        path: "/new",
        name: "new-api",
        component: new_api,
    },
];