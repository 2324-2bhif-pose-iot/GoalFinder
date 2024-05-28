<script setup>
import { ref } from "vue";

import { useRouter } from 'vue-router';
import {i18n} from "@/main.js";

const router = useRouter();

const items = ref(
    [
      {
        label: i18n.global.t("header.home"),
        command: () => {router.push("/")}
      },
      {
        label: i18n.global.t("header.games"),
        command: () => {router.push("/games")}
      },
      {
        label: i18n.global.t("header.settings"),
        command: () => {router.push("/settings")}
      }
    ]
);
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
</style>