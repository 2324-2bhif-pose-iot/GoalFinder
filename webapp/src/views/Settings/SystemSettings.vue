<script setup>

import BluetoothDevicesManager from "@/components/BluetoothDevicesManager.vue";
</script>

<template>
  <div>
    <div class="card">
      <div class="card-header">System</div>
      <div class="card-body">
        <div class="mb-3">
          <div class="card-title">System</div>
          <button class="btn btn-primary">Restart</button>
          <button class="btn btn-secondary ms-1">Factory settings</button>
        </div>
        <div class="mb-3">
          <div class="card-title">Info</div>
          <div class="row">
            <div class="col-md-5"><strong>Name:</strong></div>
            <div class="col-auto">Goalfinder</div>
          </div>
          <div class="row">
            <div class="col-md-5"><strong>Version:</strong></div>
            <div class="col-auto">1.0.0</div>
          </div>
          <div class="row">
            <div class="col-md-5"><strong>MAC address:</strong></div>
            <div class="col-auto">FF:FF:FF:FF:FF:FF</div>
          </div>
          <div class="row">
            <div class="col-md-5"><strong>Bluetooth address:</strong></div>
            <div class="col-auto">FF:FF:FF:FF:FF:FF</div>
          </div>
        </div>
        <div>
          <div class="card-title">Software update</div>
          <div>
            <p>Current version: 1.0.0</p>
            <button class="btn btn-primary">Search for update</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped>

</style>