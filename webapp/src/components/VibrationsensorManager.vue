<template>
  <div>
    <div id="vb">
      <div class="label-container">
        <label for="sensitivity">{{ $t("word.sensitivity") }}</label>
        <div class="button-container">
          <Button class="button" @click="setSensitivity(25)">25%</Button>
          <Button class="button" @click="setSensitivity(50)">50%</Button>
          <Button class="button" @click="setSensitivity(100)">100%</Button>
        </div>
      </div>
    </div>
    <div class="current-sensitivity">
      <span>{{ $t("word.curr_sensitivity") }}: {{ settings.vibrationSensorSensitivity }}%</span>
    </div>
    <transition name="fade">
      <div v-if="message" class="message">{{ message }}</div>
    </transition>
  </div>
</template>

<script setup>
import Button from 'primevue/button';
import { useSettingsStore } from "@/stores/settings.js";
import { ref } from 'vue';

const settings = useSettingsStore();
const message = ref("");

const setSensitivity = (value) => {
  settings.vibrationSensorSensitivity = value;
  message.value = `${$t("word.sensitivity_set_to")}: ${settings.vibrationSensorSensitivity}%`;

  setTimeout(() => {
    message.value = '';
  }, 3000);
};
</script>

<style scoped>
.label-container {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 1rem;
  margin-top: 0.5rem;
}

.button-container {
  display: flex;
}

.button {
  margin-left: 10px;
}

.button:first-child {
  margin-left: 0;
}

.button:hover {
  background-color: #45a049;
}

.current-sensitivity {
  text-align: center;
  margin-top: 0.2rem;
}

.current-sensitivity span {
  margin-left: 0.1rem;
}

.message {
  margin-top: 0.1rem;
  padding: 0.7rem;
  background-color: #e7f3e7;
  color: #2c662d;
  border: 1px solid #2c662d;
  border-radius: 0.05rem;
  opacity: 1;
  transition: opacity 0.5s ease-in-out;
}

span {
  text-align: center;
  margin-top: 0.1rem;
  font-weight: bold;
}
</style>
