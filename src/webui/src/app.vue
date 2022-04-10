<template>
    <div>
        <nav class="navbar navbar-dark bg-dark navbar-expand-lg shadow">
            <div class="container-fluid">
                <span class="navbar-brand mb-0 h1">OpenCAPIF</span>
                <button
                    class="navbar-toggler"
                    type="button"
                    data-bs-toggle="collapse"
                    data-bs-target="#navbarNav"
                    aria-controls="navbarNav"
                    aria-expanded="false"
                    aria-label="Toggle navigation"
                >
                    <span class="navbar-toggler-icon"></span>
                </button>
                <div class="collapse navbar-collapse" id="navbarNav">
                    <ul class="navbar-nav">
                        <li class="nav-item">
                            <router-link class="nav-link" to="/">Published APIs</router-link>
                        </li>
                        <li class="nav-item">
                            <router-link class="nav-link" to="/logs">Invocation Logs</router-link>
                        </li>
                    </ul>
                </div>
            </div>
        </nav>
        <div class="mx-auto col-md-6 col-sm-10 mt-5">
            <router-view></router-view>
        </div>
    </div>
</template>

<script>
export default {
    name: "app",
};
</script>

<style scoped>
router-link:hover {
    cursor: pointer;
}
</style>
