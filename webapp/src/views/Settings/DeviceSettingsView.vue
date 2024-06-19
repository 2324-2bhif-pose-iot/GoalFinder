<script setup>

import VibrationsensorManager from "@/components/Icons/VibrationsensorManager.vue";
import LedManager from "@/components/Icons/LedManager.vue";
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