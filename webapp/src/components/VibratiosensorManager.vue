<template>
  <div>
    <div id="vb">
      <div class="label-container">
        <label for="sensitivity">{{ $t("word.sensitivity") }}</label>
        <div class="button-container">
          <Button class="button" @click="setSensitivity(25)">25%</Button>
          <Button class="button" @click="setSensitivity(50)">50%</Button>
          <Button class="button" @click="setSensitivity(75)">75%</Button>
          <Button class="button" @click="setSensitivity(100)">100%</Button>
        </div>
      </div>
    </div>
    <div class="current-sensitivity">
      <span>{{ $t("word.curr_sensitivity") }}: {{ settings.vibrationSensorSensitivity }}%</span>
    </div>
  </div>
</template>

<script setup lang="ts">
import Button from "@/components/Button.vue";
import { useSettingsStore } from "@/stores/settings";

const settings = useSettingsStore();

const setSensitivity = (value: number) => {
  settings.vibrationSensorSensitivity = value;
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

.current-sensitivity {
  text-align: center;
  margin-top: 0.2rem;
}

.current-sensitivity span {
  margin-left: 0.1rem;
}

span {
  text-align: center;
  margin-top: 0.1rem;
  font-weight: bold;
}
</style>
