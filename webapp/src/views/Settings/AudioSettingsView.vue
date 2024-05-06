<script setup>
  import {useSettingsStore} from "@/stores/settings.js";

  const settings = useSettingsStore();
</script>

<template>
  <div>
    <Card>
      <template #title>Audio</template>
      <template #content>
        <div id="volume-slider-control">
          <label>Volume</label>
          <Slider id="volume-slider" v-model="settings.volume"/>
        </div>
      </template>
    </Card>
  </div>
</template>

<style scoped>

  #volume-slider-control {
    display: flex;
    align-items: center;
    flex-wrap: wrap;
  }

  #volume-slider {
    margin-left: auto;
    width: 80%;
  }
</style>