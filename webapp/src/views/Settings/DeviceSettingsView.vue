<script setup>

import VibrationsensorManager from "@/components/VibrationsensorManager.vue";
import LedManager from "@/components/LedManager.vue";
</script>

<template>
  <div>
    <Card>
      <template #title>
        {{ $t("settings.devices") }}
      </template>
      <template #content>
        <VibrationsensorManager/>
        <LedManager/>
      </template>
    </Card>
  </div>
</template>

<style scoped>

</style>