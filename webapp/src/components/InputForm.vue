<script setup lang="ts">
  const props = defineProps([
    'label',
    'placeholder',
    'type'
  ]);

  const model = defineModel();
</script>

<template>
  <div class="input-container">
    <label :for="$.uid.toString()">{{ label }}</label>
    <input :id="$.uid.toString()" :type="type" :placeholder="placeholder" v-model="model"/>
  </div>
</template>

<style scoped>
  .input-container {
    display: flex;
    flex-direction: column;
    gap: 0.3rem;
  }

  .input-container > label {
    margin-left: 0.3rem;
  }

  .input-container > input {
    padding: 0.5rem;
    border-radius: var(--corner-radius);
    border: 2px solid var(--border-color);
    background: var(--card-background-color);
    font-size: inherit;
    transition: 0.4s;
    color: var(--text-color);
    outline: none;
  }

  .input-container > input:focus {
    border-color: cornflowerblue;
  }
</style>