<script setup>
import {ref, watch} from "vue";

import { useRouter } from 'vue-router';
import {i18n} from "@/main.js";
import {useSettingsStore} from "@/stores/settings.js";

const router = useRouter();

const items = ref(
    [
      {
        label: i18n.global.t("header.home"),
        command: () => {router.push("/")}
      },
      {
        label: i18n.global.t("header.sessions"),
        command: () => {router.push("/list")}
      },
      {
        label: i18n.global.t("header.settings"),
        command: () => {router.push("/settings")}
      }
    ]
);

const settings = useSettingsStore();

watch(() => settings.enableDarkMode, value => {
  let label = document.getElementById("dark-mode-switch-label");
  if(value === true) {
    label.innerText = i18n.global.t("word.dark");
  } else {
    label.innerText = i18n.global.t("word.light");
  }
});

</script>

<template>
  <div>
    <Menubar :model="items">
      <template #start>
        <div class="me-2">
          Goal Finder
        </div>
      </template>
      <template #end>
        <div>
         <div id="dark-mode-switch-container">
           <label id="dark-mode-switch-label">{{ $t("word.light") }}</label>
           <InputSwitch v-model="settings.enableDarkMode"/>
         </div>
          <router-link to="/about">
            <Button severity="secondary" text>
              {{ $t("header.about") }}
            </Button>
          </router-link>
        </div>
      </template>
    </Menubar>
  </div>
</template>

<style scoped>
  #dark-mode-switch-container {
    display: inline-flex;
    flex-wrap: wrap;
    gap: 0.5rem;
    align-items: center;
    margin-bottom: 0.3rem;
  }
</style>