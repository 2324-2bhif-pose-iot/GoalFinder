<script setup>

import BluetoothDevicesManager from "@/components/BluetoothDevicesManager.vue";
import VibrationsensorManager from "@/components/Icons/VibrationsensorManager.vue";
</script>

<template>
  <div>
    <Card>
      <template #title>
        {{ $t("settings.devices") }}
      </template>
      <template #content>
        <VibrationsensorManager/>
      </template>
    </Card>
  </div>
</template>

<style scoped>

</style>