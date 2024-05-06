<script setup>
  import {useSettingsStore} from "@/stores/settings.js";

  const settings = useSettingsStore();
</script>

<template>
  <div>
    <Card>
      <template #title>General</template>
      <template #content>
        <div class="input-form mb-3">
          <label for="device-name">Device name</label>
          <InputText id="device-name" v-model="settings.deviceName" aria-describedby="device-name-help" />
          <small id="device-name-help">Enter a name for the device.</small>
        </div>
        <div class="input-form mb-3">
          <label for="device-password">Device password</label>
          <Password id="device-password" :feedback="false" v-model="settings.devicePassword" aria-describedby="device-password-help" />
          <small id="device-password-help">Enter a password for the device.</small>
        </div>
      </template>
    </Card>
  </div>

</template>

<style scoped>
  .input-form {
    display: flex;
    flex-direction: column;
    gap: 0.3rem;
  }
</style>