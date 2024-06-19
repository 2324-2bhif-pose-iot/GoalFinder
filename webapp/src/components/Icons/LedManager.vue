<script setup>
import { ref } from 'vue';
import Button from 'primevue/button';
import {useSettingsStore} from "@/stores/settings.js";

const message = ref('');
const settings = useSettingsStore();

function setLedModus(value) {
  settings.ledModus = value;
  message.value = `Modus set to: ${settings.ledModus}`;
  console.log(message.value);
}
</script>

<template>
  <div>
    <div id="led">
      <div class="label-container">
        <label for="modus">Set Modus of LED</label>
        <div class="button-container">
          <Button class="button" @click="setLedModus(1)">Standard</Button>
          <Button class="button" @click="setLedModus(2)">Fade</Button>
          <Button class="button" @click="setLedModus(3)">Flash</Button>
          <Button class="button" @click="setLedModus(4)">Turbo</Button>
        </div>
      </div>
    </div>
    <div class="current-modus">
      <span>Current Modus: {{ settings.ledModus }}</span>
    </div>
    <transition name="fade">
      <div v-if="message" class="message">{{ message }}</div>
    </transition>
  </div>
</template>

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

.current-modus {
  text-align: center;
  margin-top: 0.2rem;
}

.current-modus span {
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

.fade-enter-active,
.fade-leave-active {
  transition: opacity 0.5s;
}

.fade-enter,
.fade-leave-to {
  opacity: 0;
}
</style>