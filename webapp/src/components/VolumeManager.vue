<script setup lang="ts">
import {ref} from "vue";
import {useSettingsStore} from "@/stores/settings";
import Button from "@/components/Button.vue";

const settings = useSettingsStore();

// Lautstärke setzen
const setVolume = (value: number) => {
  settings.volume = value;
};

const setMetronomeSound = (value: number) => {
  settings.metronomeSound = value;
}

const setHitSound = (value: number) => {
  settings.hitSound = value;
};

const setMissSound = (value: number) => {
  settings.missSound = value;
};

</script>

<template>
  <div class="volume-slider-control">
    <label>{{ $t("word.volume") }}</label>
    <div class="button-container">
      <Button class="button" @click="setVolume(0)">0%</Button>
      <Button class="button" @click="setVolume(25)">25%</Button>
      <Button class="button" @click="setVolume(50)">50%</Button>
      <Button class="button" @click="setVolume(75)">75%</Button>
      <Button class="button" @click="setVolume(100)">100%</Button>
    </div>
  </div>
  <div class="current-value">
    {{ $t("word.curr_volume") }}: {{ settings.volume }}%
  </div>

  <div class="sound-select">
    <label>Metronome Sound</label>
    <div class="button-container">
      <Button class="button" @click="setMetronomeSound(0)">Sound 1</Button>
      <Button class="button" @click="setMetronomeSound(1)">Sound 2</Button>
      <Button class="button" @click="setMetronomeSound(2)">Sound 3</Button>
    </div>
  </div>
  <div class="current-value">
    Current Metronome Sound: {{ settings.metronomeSound + 1 }}
  </div>

  <div class="sound-select">
    <label>Hit Sound</label>
    <div class="button-container">
      <Button class="button" @click="setHitSound(0)">Sound 1</Button>
      <!-- <Button class="button" @click="setHitSound(1)">Sound 2</Button>
      <Button class="button" @click="setHitSound(2)">Sound 3</Button> -->
    </div>
  </div>
  <div class="current-value">
    Current Hit Sound: {{ settings.hitSound + 1 }}
  </div>

  <div class="sound-select">
    <label>Miss Sound</label>
    <div class="button-container">
      <Button class="button" @click="setMissSound(0)">Sound 1</Button>
      <Button class="button" @click="setMissSound(1)">Sound 2</Button>
      <Button class="button" @click="setMissSound(2)">Sound 3</Button>
    </div>
  </div>
  <div class="current-value">
    Current Miss Sound : {{ settings.missSound + 1 }}
  </div>
</template>

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

.current-value {
  text-align: center;
  margin-top: 0.1rem;
  font-weight: bold;
}

.sound-select {
  display: flex;
  align-items: center;
  margin-top: 1rem;
}
</style>
