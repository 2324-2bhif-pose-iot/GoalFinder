<script setup lang="ts">
import SoftwareUpdateModal from "@/components/SoftwareUpdateModal.vue";
import Button from "@/components/Button.vue";
import {useTemplateRef} from "vue";
import {useSettingsStore} from "@/stores/settings";

const settings = useSettingsStore();

const updateDialog = useTemplateRef<typeof SoftwareUpdateModal>("updateDialog");

const openUpdateDialog = () => {
  updateDialog.value?.show();
};

</script>

<template>
  <h3>{{ $t("settings.system") }}</h3>
  <h4>{{ $t("settings.system") }}</h4>
  <div id="system-buttons">
    <Button @click="settings.restartDevice()" primary>{{ $t("word.restart") }}</Button>
    <Button @click="settings.restartDevice()">{{ $t("word.factory_settings_reset") }}</Button>
  </div>
  <h4>Info</h4>
  <div id="device-info">
    <div>
      <div class="property-title">{{ $t("word.device_name") }}</div>
      <div>{{ settings.deviceName }}</div>
    </div>
    <div>
      <div class="property-title">{{ $t("word.curr_version") }}</div>
      <div>1.0.0</div>
    </div>
    <div>
      <div class="property-title">{{ $t("word.mac_address") }}</div>
      <div>{{ settings.macAddress }}</div>
    </div>
  </div>
  <h4>{{ $t("word.software_update") }}</h4>
  <Button primary @click="openUpdateDialog">{{ $t("word.search_for_update") }}</Button>
  <SoftwareUpdateModal ref="updateDialog"/>
</template>

<style scoped>

#system-buttons {
  display: flex;
  gap: 0.4rem;
  flex-wrap: wrap;
}

#device-info {
  margin-top: 0;
  display: flex;
  flex-direction: column;
  justify-content: space-between;
  gap: 0.3rem;
}

#device-info > div {
  display: flex;
  flex-wrap: wrap;
  flex-direction: row;
}

.property-title {
  width: 25vmin;
  font-weight: bold;
}

h4 {
  color: cornflowerblue;
}

</style>