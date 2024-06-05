<script setup>
import WiFiManager from "@/components/WiFiManager.vue";
</script>

<template>
  <div>
    <Card>
      <template #title>{{ $t("settings.wifi") }}</template>
      <template #content>
        <WiFiManager/>
      </template>
    </Card>
  </div>
</template>

<style scoped>

</style>