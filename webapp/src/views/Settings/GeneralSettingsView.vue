<script setup lang="ts">
import InputForm from "@/components/InputForm.vue";
import {useSettingsStore} from "@/stores/settings";

const settings = useSettingsStore();

function isSSIDValid(value: string) {
  const regex = /^[a-zA-Z0-9_]+$/;
  if (value == null || value.length < 3 || value.length > 32 || !regex.test(value)) {
    settings.isValid = false;
    return false;
  }
  settings.isValid = true;
  return true;
}
</script>

<template>
  <h3>{{ $t("settings.general") }}</h3>
  <h4>Info</h4>
  <form id="general-input">
    <InputForm v-model="settings.deviceName" :label="$t('word.device_name')"
               :placeholder="$t('description.device_name_description')" type="text"/>
    <InputForm v-model="settings.devicePassword" :label="$t('word.device_password')"
               :placeholder="$t('description.device_password_description')" type="password"/>
  </form>
</template>

<style scoped>
#general-input {
  display: flex;
  flex-direction: column;
  gap: 1rem;
}
</style>