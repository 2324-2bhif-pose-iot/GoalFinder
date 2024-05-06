<script setup>
  import {useSettingsStore} from "@/stores/settings.js";

  const settings = useSettingsStore();
</script>

<template>
  <div>
    <Card>
      <template #title>System</template>
      <template #content>
        <div class="mb-3">
          <div class="mb-2">System</div>
          <Button>Restart</Button>
          <Button class="ms-1" severity="danger">Factory settings</Button>
        </div>
        <div class="mb-3">
          <div>Info</div>
          <div class="row">
            <div class="col-md-5"><strong>Name:</strong></div>
            <div class="col-auto">{{settings.deviceName}}</div>
          </div>
          <div class="row">
            <div class="col-md-5"><strong>Version:</strong></div>
            <div class="col-auto">1.0.0</div>
          </div>
          <div class="row">
            <div class="col-md-5"><strong>MAC address:</strong></div>
            <div class="col-auto">{{settings.macAddress}}</div>
          </div>
          <div class="row">
            <div class="col-md-5"><strong>Bluetooth address:</strong></div>
            <div class="col-auto">{{settings.bluetoothAddress}}</div>
          </div>
        </div>
        <div>
          <div>Software update</div>
          <div>
            <p>Current version: 1.0.0</p>
            <Button>Search for update</Button>
          </div>
        </div>
      </template>
    </Card>
  </div>
</template>

<style scoped>

</style>