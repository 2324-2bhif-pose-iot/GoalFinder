<script setup lang="ts">
import BluetoothManager from "@/components/BluetoothManager.vue";
import LedManager from "@/components/LedManager.vue";
import VibrationSensorManager from "@/components/VibratiosensorManager.vue";
import LaserSensorManager from "@/components/LaserSensorManager.vue";
</script>

<template>
  <h3>{{ $t("settings.devices") }}</h3>
  <h4>Lighting</h4>
  <LedManager/>
  <h4>Sensors</h4>
  <VibrationSensorManager/>
  <LaserSensorManager/>
  <h4>Bluetooth</h4>
  <BluetoothManager/>
</template>

<style scoped>

</style>