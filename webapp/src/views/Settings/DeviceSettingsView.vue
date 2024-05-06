<script setup>

import BluetoothDevicesManager from "@/components/BluetoothDevicesManager.vue";
</script>

<template>
  <div>
    <Card>
      <template #title>
        Devices
      </template>
      <template #content>
        <BluetoothDevicesManager/>
      </template>
    </Card>
  </div>
</template>

<style scoped>

</style>