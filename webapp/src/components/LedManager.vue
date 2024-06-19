<script setup>
import { ref } from 'vue';
import Button from 'primevue/button';
import { useSettingsStore } from "@/stores/settings.js";

const message = ref('');
const settings = useSettingsStore();

function setLedMode(value) {
  settings.ledMode = value;
  message.value = `${$t("word.curr_mode")}: ${settings.ledMode}`;
}
</script>

<template>
  <div>
    <div id="led">
      <div class="label-container">
        <label for="modus">{{ $t("word.led_mode") }}</label>
        <div class="button-container">
          <Button class="button" @click="setLedMode(1)">{{ $t("word.standard") }}</Button>
          <Button class="button" @click="setLedMode(2)">{{ $t("word.fade") }}</Button>
          <Button class="button" @click="setLedMode(3)">{{ $t("word.flash") }}</Button>
          <Button class="button" @click="setLedMode(4)">{{ $t("word.turbo") }}</Button>
        </div>
      </div>
    </div>
    <div class="current-modus">
      <span>{{ $t("word.curr_mode") }}: {{ settings.ledMode }}</span>
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
</style>
