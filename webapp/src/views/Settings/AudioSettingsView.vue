<template>
  <div>
    <Card>
      <template #title>Audio</template>
      <template #content>
        <div class="volume-slider-control">
          <label>{{ $t("word.volume") }}</label>
          <div class="button-container">
            <Button class="volume-button" @click="setVolume(25)">25%</Button>
            <Button class="volume-button" @click="setVolume(50)">50%</Button>
            <Button class="volume-button" @click="setVolume(100)">100%</Button>
          </div>
        </div>
        <div class="current-volume">{{ $t("word.curr_volume") }}: {{ settings.volume }}%</div>
        <div v-if="message" class="alert-message">{{ message }}</div>
      </template>
    </Card>
  </div>
</template>

<script setup>
import { useSettingsStore } from "@/stores/settings.js";
import Button from "primevue/button";
import { ref } from 'vue';

const settings = useSettingsStore();
let message = ref('');

const setVolume = (value) => {
  settings.volume = value;
  message.value = `${$t("word.volume")} ${settings.volume}%`;
  setTimeout(() => {
    message.value = '';
  }, 3000);
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
}

.volume-button {
  margin-left: 0.1rem;
}

.volume-button:hover {
  background-color: #45a049;
}

.current-volume {
  text-align: center;
  margin-top: 0.1rem;
  font-weight: bold;
}

.alert-message {
  margin-top: 1rem;
  padding: 0.7rem;
  background-color: #e7f3e7;
  color: #2c662d;
  border: 1px solid #2c662d;
  border-radius: 0.05rem;
  opacity: 1;
  transition: opacity 0.5s ease-in-out;
}
</style>
