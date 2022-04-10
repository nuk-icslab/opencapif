<template>
  <div>
    <div class="row justify-content-between mb-3">
      <div class="col-5">
        <input type="text" class="form-control" v-model="apf_id" placeholder="AEF ID" />
      </div>
      <div class="col-5">
        <input type="text" class="form-control" v-model="invkr_id" placeholder="Invoker ID" />
      </div>
      <div class="col-1">
        <button class="btn btn-primary" type="button" @click="queryApf">Query</button>
      </div>
    </div>
    <table class="table table-striped table-sm table-responsive">
      <thead>
        <tr>
          <th scope="col">Time</th>
          <th scope="col">API Name</th>
          <th scope="col">Version</th>
          <th scope="col">Resource</th>
          <th scope="col">Operation</th>
          <th scope="col">Result</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="log in logs">
          <td>{{ log.name }}</td>
          <td>{{ api.aef_id }}</td>
          <td>{{ api.versions.join(', ') }}</td>
          <td>{{ api.domain }}</td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<script>
export default {
  name: "logs",
  data() {
    return {
      aef_id: "",
      invkr_id: ""
    };
  },
  methods: {
  },
};
</script>

<style scoped>
</style>