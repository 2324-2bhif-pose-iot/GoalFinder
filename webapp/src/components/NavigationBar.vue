<script setup>
import { ref } from "vue";

import { useRouter } from 'vue-router';

const router = useRouter();

const items = ref(
    [
      {
        label: "Home",
        command: () => {router.push("/")}
      },
      {
        label: "Games",
        command: () => {router.push("/games")}
      },
      {
        label: "Settings",
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
            <Button label="About" severity="secondary" text/>
          </router-link>
        </div>
      </template>
    </Menubar>
  </div>
</template>

<style scoped>
</style>