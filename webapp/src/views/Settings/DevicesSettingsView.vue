<script setup lang="ts">
import BluetoothManager from "@/components/BluetoothManager.vue";
import LedManager from "@/components/LedManager.vue";
import VibrationSensorManager from "@/components/VibratiosensorManager.vue";
</script>

<template>
  <h3>{{ $t("settings.devices") }}</h3>
  <LedManager/>
  <VibrationSensorManager/>
  <BluetoothManager/>
</template>

<style scoped>

</style>