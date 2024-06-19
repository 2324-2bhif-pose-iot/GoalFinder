<script setup>

import LedManager from "@/components/LedManager.vue";
</script>

<template>
  <div>
    <Card>
      <template #title>
        {{ $t("settings.devices") }}
      </template>
      <template #content>
        <LedManager/>
      </template>
    </Card>
  </div>
</template>

<style scoped>

</style>