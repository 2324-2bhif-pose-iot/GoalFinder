<script setup>
import GameListItem from "@/components/GameListItem.vue";
const game1 = {
  teamOne: "L",
  teamTwo: "B",
  goalsTeamTwo: 1,
  goalsTeamOne: 2,
  playTime : 45
}
</script>

<template>
  <div class="container">
    <h1>Game Configuration</h1>
    <br>
    <h3>Last Games</h3>
    <ul class="list-group">
      <li class="list-group-item"><GameListItem v-bind="game1"/></li>
    </ul>
  </div>
</template>

<style scoped>

</style>