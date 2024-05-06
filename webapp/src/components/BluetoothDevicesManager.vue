<script setup>
  import {useSettingsStore} from "@/stores/settings.js";

  const settings = useSettingsStore();
</script>

<template>
  <div>
    <div id="bluetooth-enable">
      <label>Bluetooth</label>
      <InputSwitch v-model="settings.isBluetoothEnabled" id="switch" />
    </div>
    <div v-show="settings.isBluetoothEnabled">
      <div class="mt-3">
        <small>Connected devices</small>
        <Listbox :options="settings.connectedBluetoothDevices" class="mt-1" listStyle="max-height:15rem"/>
      </div>
      <div class="mt-3">
        <small>Available devices</small>
        <Listbox :options="settings.availableBluetoothDevices" class="mt-1" listStyle="max-height:15rem"/>
      </div>
    </div>
  </div>
</template>

<style scoped>
  #bluetooth-enable {
      display: flex;
      align-items: center;
      gap: 2rem;
  }

  #switch {
    margin-left: auto;
  }
</style>