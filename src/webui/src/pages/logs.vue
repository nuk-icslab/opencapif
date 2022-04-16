<template>
  <div>
    <div class="row justify-content-between mb-3">
      <div class="col-5">
        <input type="text" class="form-control" v-model="aef_id" placeholder="AEF ID" />
      </div>
      <div class="col-5">
        <input type="text" class="form-control" v-model="invkr_id" placeholder="Invoker ID" />
      </div>
      <div class="col-1">
        <button class="btn btn-primary" type="button" @click="queryLog">Query</button>
      </div>
    </div>
    <table class="table table-striped table-sm table-responsive">
      <thead>
        <tr>
          <th scope="col">Time</th>
          <th scope="col">API Name</th>
          <th scope="col">Version</th>
          <th scope="col">Resource</th>
          <!-- <th scope="col">Operation</th> -->
          <th scope="col">Result</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="log in logs">
          <td>{{ log.time }}</td>
          <td>{{ log.api_name }}</td>
          <td>{{ log.version }}</td>
          <td>{{ log.resource }}</td>
          <!-- <td>{{ log.operation }}</td> -->
          <td>{{ log.result }}</td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<script>
const { ccfUrl } = require('../../config/ccf.js');
const capifWebUiClient = require('capif-webui-client');
const { ApiClient, DefaultApi, ServiceAPIDescription } = capifWebUiClient;
export default {
  name: "logs",
  data() {
    return {
      aef_id: "",
      invkr_id: "",
      logs: []
    };
  },
  methods: {
    queryLog: function () {
      const my_api_client = new ApiClient(ccfUrl);
      const my_default_api = new DefaultApi(my_api_client);

      let opts = {};

      if (this.aef_id !== "") {
        opts['aefId'] = this.aef_id;
      }
      if (this.invkr_id !== "") {
        opts['apiInvokerId'] = this.invkr_id;
      }

      let callback = (error, data) => {
        if (error) {
          console.error(error);
        } else {
          this.logs = data['logs'].map(log => {
            let time = new Date(log['invocationTime']);
            console.log(typeof (time));
            //console.log(time.toISOString());
            return {
              time,
              api_name: log['apiName'],
              version: log['apiVersion'],
              resource: log['resourceName'],
              operation: log['operation'],
              result: log['result']
            }
          })
        }
      };
      my_default_api.logsV1ApiInvocationLogsGet(opts, callback);
    }
  },
};
</script>

<style scoped>
</style>