<script setup>

import BluetoothDevicesManager from "@/components/BluetoothDevicesManager.vue";
import VibrationsensorManager from "@/components/Icons/VibrationsensorManager.vue";
</script>

<template>
  <div>
    <Card>
      <template #title>
        Devices
      </template>
      <template #content>
        <BluetoothDevicesManager/>
        <VibrationsensorManager/>
      </template>
    </Card>
  </div>
</template>

<style scoped>

</style>