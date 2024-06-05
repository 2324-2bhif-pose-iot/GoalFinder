<script setup>
  import {useSettingsStore} from "@/stores/settings.js";

  const settings = useSettingsStore();
</script>

<template>
  <div>
    <div id="wifi-enable">
      <label>{{ $t("settings.wifi") }}</label>
      <InputSwitch v-model="settings.isWifiEnabled" id="switch" />
    </div>
    <div v-show="settings.isWifiEnabled">
      <div class="mt-3">Status: Not connected</div>
      <Listbox :options="settings.availableNetworks" class="mt-3"/>
      <Button class="mt-3">{{ $t("word.refresh") }}</Button>
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