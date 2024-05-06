<script setup>
  import {useSettingsStore} from "@/stores/settings.js";

  const settings = useSettingsStore();
</script>

<template>
  <div>
    <div id="wifi-enable">
      <label>WiFi</label>
      <InputSwitch v-model="settings.isWifiEnabled" id="switch" />
    </div>
    <div v-show="settings.isWifiEnabled">
      <div class="mt-3">Status: Not connected</div>
      <Listbox :options="settings.availableNetworks" class="mt-3"/>
      <Button label="Refresh" class="mt-3"/>
    </div>
  </div>
</template>

<style scoped>
  #wifi-enable {
    display: flex;
    align-items: center;
    gap: 2rem;
  }

  #switch {
    margin-left: auto;
  }
</style>