<script setup>
  import {useSettingsStore} from "@/stores/settings.js";

  const settings = useSettingsStore();
</script>

<template>
  <div>
    <Card>
      <template #title>{{ $t("settings.system") }}</template>
      <template #content>
        <div class="mb-3">
          <h4 class="mb-2">{{ $t("settings.system") }}</h4>
          <Button>{{ $t("word.restart") }}</Button>
          <Button class="ms-1" severity="danger">{{ $t("word.factory_settings_reset") }}</Button>
        </div>
        <div class="mb-3">
          <h4>Info</h4>
          <div class="row">
            <div class="col-md-5"><strong>{{ $t("word.device_name") }}</strong></div>
            <div class="col-auto">{{settings.deviceName}}</div>
          </div>
          <div class="row">
            <div class="col-md-5"><strong>{{ $t("word.curr_version") }}</strong></div>
            <div class="col-auto">1.0.0</div>
          </div>
          <div class="row">
            <div class="col-md-5"><strong>{{ $t("word.mac_address") }}</strong></div>
            <div class="col-auto">{{settings.macAddress}}</div>
          </div>
          <div class="row">
            <div class="col-md-5"><strong>{{ $t("word.bluetooth_address") }}</strong></div>
            <div class="col-auto">{{settings.bluetoothAddress}}</div>
          </div>
        </div>
        <div>
          <h4>{{ $t("word.software_update") }}</h4>
          <div>
            <p>{{ $t("word.curr_version") }}: 1.0.0</p>
            <a href="/update">
              <Button>{{ $t("word.search_for_update") }}</Button>
            </a>
          </div>
        </div>
      </template>
    </Card>
  </div>
</template>

<style scoped>

</style>
