<script setup>
import VibrationsensorManager from "@/components/VibrationsensorManager.vue";
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