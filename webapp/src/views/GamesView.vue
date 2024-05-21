<script setup>
import GameListItem from "@/components/GameListItem.vue";
import {ref} from "vue";
import Game from "@/models/game.js";
import Team from "@/models/team.js";

const teamOne = new Team("LASK");
const teamTwo = new Team("Blau Weiß Linz");
teamOne.scoreGoal();
teamOne.scoreGoal();

teamTwo.scoreGoal();

const game = new Game(teamOne, teamTwo, new Date(2024, 5, 5));
const game1 = new Game(teamTwo, teamOne, new Date(2024, 11, 5));
game1.Duration = 5300;
game.Duration = 5400;
const games = [];
games.push(game);
games.push(game1);

const sortKey = ref();
const sortOrder = ref();
const sortField = ref();
const sortOptions = ref([
  {label: 'Date High to Low', value: '!Date'},
  {label: 'Date Low to High', value: 'Date'},
]);

const onSortChange = (event) => {
  const value = event.value.value;
  const sortValue = event.value;

  if (value.indexOf('!') === 0) {
    sortOrder.value = -1;
    sortField.value = value.substring(1, value.length);
    sortKey.value = sortValue;
  }
  else {
    sortOrder.value = 1;
    sortField.value = value;
    sortKey.value = sortValue;
  }
};

</script>

<template>
  <div class="container">
    <h1>Games Configuration</h1>
    <Card>
      <template #content>
        <DataView :value="games" paginator :rows="6" :sortOrder="sortOrder" :sortField="sortField">
          <template #header>
            <div id="card-header">
              <Dropdown v-model="sortKey" :options="sortOptions" optionLabel="label" placeholder="Sort By Date" @change="onSortChange($event)" />
              <Button id="new-game-button" label="Create new game"/>
            </div>

          </template>
          <template #list="slotProps">
            <div v-for="(item, index) in slotProps.items" :key="index" class="col-12">
              <GameListItem :game="item"/>
            </div>
          </template>
        </DataView>
      </template>
    </Card>

  </div>
</template>

<style scoped>
  #card-header {
    display: flex;
  }

  #new-game-button {
    margin-left: auto;
  }
</style>