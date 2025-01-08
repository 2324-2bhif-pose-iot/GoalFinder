<script setup lang="ts">
import Button from "@/components/Button.vue";

const model = defineModel({type: Boolean});
</script>

<template>
  <Button :primary="model" @click="model = !model">
    <slot/>
  </Button>
</template>

<style scoped>

</style>