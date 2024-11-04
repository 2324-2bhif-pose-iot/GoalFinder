<script setup lang="ts">
import LedManager from "@/components/LedManager.vue";
import VibrationSensorManager from "@/components/VibrationSensorManager.vue";
</script>

<template>
  <h3>{{ $t("settings.devices") }}</h3>
  <LedManager/>
  <VibrationSensorManager/>
</template>

<style scoped>

</style>