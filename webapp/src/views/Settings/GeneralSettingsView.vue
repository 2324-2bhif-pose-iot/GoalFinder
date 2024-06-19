<script setup>
  import {useSettingsStore} from "@/stores/settings.js";

  const settings = useSettingsStore();

  function isSSIDValid(value)
  {
      const regex = /^[a-zA-Z0-9_]+$/;
      if(value == null || value < 3 || value > 32 || !regex.test(value))
      {
          return false;
      }

      return true;
  }
</script>

<template>
  <div>
    <Card>
      <template #title>{{ $t("settings.general") }}</template>
      <template #content>
        <div class="input-form mb-3">
          <label for="device-name">{{ $t("word.device_name") }}</label>
          <InputText id="device-name" v-model="settings.deviceName" aria-describedby="device-name-help" :invalid="!isSSIDValid(settings.deviceName)" />
          <small id="device-name-help">{{ $t("description.device_name_description") }}</small>
        </div>
        <!--
        <div class="input-form mb-3">
          <label for="device-password">{{ $t("word.device_password") }}</label>
          <Password id="device-password" :feedback="false" v-model="settings.devicePassword" aria-describedby="device-password-help" />
          <small id="device-password-help">{{ $t("description.device_password_description") }}</small>
        </div>
        --->
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