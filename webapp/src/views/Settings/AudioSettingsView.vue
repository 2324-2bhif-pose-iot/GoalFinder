<template>
  <div>
    <Card>
      <template #title>Audio</template>
      <template #content>
        <div class="volume-slider-control">
          <label>{{ $t("word.volume") }}</label>
          <div class="button-container">
            <Button class="button" @click="setVolume(25)">25%</Button>
            <Button class="button" @click="setVolume(50)">50%</Button>
            <Button class="button" @click="setVolume(75)">75%</Button>
            <Button class="button" @click="setVolume(100)">100%</Button>
          </div>
        </div>
        <div class="current-volume">{{ $t("word.curr_volume") }}: {{ settings.volume }}%</div>
      </template>
    </Card>
  </div>
</template>

<script setup>
import { useSettingsStore } from "@/stores/settings.js";
import Button from "primevue/button";

const settings = useSettingsStore();

const setVolume = (value) => {
  settings.volume = value;
};
</script>

<style scoped>
.volume-slider-control {
  display: flex;
  align-items: center;
  flex-wrap: wrap;
}

.button-container {
  margin-left: auto;
  display: flex;
}

.button {
  margin-left: 10px;
}

.button:first-child {
  margin-left: 0;
}

.current-volume {
  text-align: center;
  margin-top: 0.1rem;
  font-weight: bold;
}
</style>
