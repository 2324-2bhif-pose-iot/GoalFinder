<script setup>
import { ref } from 'vue';
import Button from 'primevue/button';
import { useSettingsStore } from "@/stores/settings.js";

const settings = useSettingsStore();

function setLedMode(value) {
  settings.ledMode = value;
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
          <Button class="button" @click="setLedMode(5)">{{ $t("word.off") }}</Button>
        </div>
      </div>
    </div>
    <div class="current-modus">
      <span>{{ $t("word.curr_mode") }}: {{ settings.ledMode }}</span>
    </div>
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

span {
  text-align: center;
  margin-top: 0.1rem;
  font-weight: bold;
}
</style>
