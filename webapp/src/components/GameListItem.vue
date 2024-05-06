<script setup>
import {computed, ref} from "vue";
import Game from "@/models/game.js";

const props = defineProps(
    {
      game: Game
    }
);

const formattedPlayTime = computed(() => {
  let seconds = props.game.Duration;
  let minutes = Math.floor(seconds / 60);
  seconds = seconds % 60;

  let result = "";

  if(minutes > 0) {
    result += minutes + " minutes ";
  }

  if(seconds > 0) {
    result += seconds + " seconds";
  }

  return result;
})

</script>

<template>
  <div id="root" class="container-fluid">
    <div class="row">
      <div class="col-md-4">
        <h3>{{game.TeamOne.Name}} vs. {{game.TeamTwo.Name}}</h3>
        <div><strong>Duration:</strong>  {{ formattedPlayTime }}</div>
      </div>
      <div id="score-container" class="col-md-4">
        <div id="scores">{{game.TeamOne.Goals}} : {{game.TeamTwo.Goals}}</div>
      </div>
      <div id="details-container" class="col-md-4">
        <div>{{ game.Date.toLocaleDateString()}}</div>
        <Button label="View details"/>
      </div>
    </div>
  </div>
</template>

<style scoped>
  #root {
    padding: 0.5rem;
  }

  #score-container {
    display: flex;
    align-items: center;
    justify-content: center;
  }

  #scores {
    font-size: 2em;
    font-weight: bold;
  }

  #details-container {
    display: flex;
    flex-direction: column;
    align-items: end;
    justify-content: end;
    gap: 1rem;
  }
</style>