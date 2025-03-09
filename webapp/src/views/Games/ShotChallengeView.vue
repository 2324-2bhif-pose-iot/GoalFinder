<script setup lang="ts">
import Page from "@/components/Page.vue";
import Button from "@/components/Button.vue";
import {Player} from "@/models/player";
import InputForm from "@/components/InputForm.vue";
import {computed, ref, watch} from "vue";

const players = ref([] as Player[]);
const showLeaderboard = ref(false);

const newPlayerName = ref("");

let currentPlayerIndex: number = 0;
let counter = 0;

let intervalId: number;

function initCounter() {
  counter = 60;
  clearInterval(intervalId);

  intervalId = setInterval(() => {
      counter--;
  }, 1000)
}

function formatTime(ms: number) {
  const seconds = Math.floor(Math.abs(ms / 1000))
  const h = Math.floor(seconds / 3600)
  const m = Math.floor((seconds % 3600) / 60)
  const s = Math.round(seconds % 60)
  const t = [h, m > 9 ? m : h ? '0' + m : m || '0', s > 9 ? s : '0' + s]
      .filter(Boolean)
      .join(':')
  return ms < 0 && seconds ? `-${t}` : t
}

function addPerson() {
  if (newPlayerName.value) {
    if(players.value.some(player => player.name === newPlayerName.value)) {
      newPlayerName.value += " 2";
      //TODO change that no duplicates are allowed
    }

    players.value.push(new Player(newPlayerName.value));
    newPlayerName.value = "";
  }
}

function recordShot(index: number, isHit: boolean) {
  if (isHit) {
    players.value[index].addHit()
  } else {
    players.value[index].addMiss();
  }
}

function removePerson(index: number) {
  players.value.splice(index, 1);
}

function finish() {
  showLeaderboard.value = true;
}

function restart() {
  showLeaderboard.value = false;
  players.value = [];
}

const sortedPersons = computed(() => {
  return players.value.slice().sort((a, b) => {
    const diffA = a.hits - a.misses;
    const diffB = b.hits - b.misses;
    return diffB - diffA;
  })});

const prettyCounter = computed(() => {
  return formatTime(counter);
})
</script>

<template>
  <Page :title="$t('header.game_shot_challenge')">
    <div class="basketball-shot-tracker" v-if="!showLeaderboard">
      <form @submit.prevent="addPerson">
        <div>
          <label for="personName">{{ $t("word.add_person") }}</label>
          <InputForm id="personName" v-model="newPlayerName"/>
        </div>
        <div class="buttons-container">
          <Button type="submit">{{ $t("word.add_person") }}</Button>
          <Button primary @click="initCounter">Start</Button>
        </div>
      </form>

      <div v-if="players.length" id="current-player-container">
        <h1>{{ prettyCounter }}</h1>
        <h1>{{ players[currentPlayerIndex].name }}</h1>
      </div>

      <div v-if="players.length">
        <h3>{{ $t("word.person_list") }}</h3>
        <ul>
          <li v-for="(person, index) in players" :key="index">
            <span>{{ person.name }}</span>
            <div class="buttons-container">
              <Button primary @click="recordShot(index, true)">{{ $t("word.hit") }}</Button>
              <Button @click="recordShot(index, false)" severity="warning">{{ $t("word.miss") }}</Button>
              <Button @click="removePerson(index)" severity="danger">{{ $t("word.remove") }}</Button>
            </div>
          </li>
        </ul>
      </div>

      <div v-if="players.length">
        <Button primary @click="finish">{{ $t("word.finish") }}</Button>
      </div>
    </div>

    <div class="leaderboard" v-else>
      <h2>{{ $t("word.leaderboard") }}</h2>
      <ul>
        <li v-for="(person, index) in sortedPersons" :key="index"> <!-- This should be sorted persons -->
          <strong>{{ index + 1 }}. {{ person.name }}</strong> - {{ $t("word.hits") }}: {{ person.hits }}, {{ $t("word.misses") }}: {{ person.misses }}
        </li>
      </ul>
      <Button primary @click="restart">{{ $t("word.restart") }}</Button>
    </div>
  </Page>
</template>

<style scoped>

.basketball-shot-tracker form div {
  margin-bottom: 15px;
}

.basketball-shot-tracker form label {
  display: block;
  margin-bottom: 5px;
}

.basketball-shot-tracker form input {
  width: 100%;
  padding: 8px;
  box-sizing: border-box;
}

.basketball-shot-tracker ul, .leaderboard ul {
  list-style-type: none;
  padding: 0;
}

.basketball-shot-tracker li, .leaderboard li {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 10px;
}

.buttons-container {
  display: flex;
  gap: 10px;
}

#current-player-container {
  align-items: center;
  display: flex;
  flex-direction: column;
  justify-content: center;
  flex-wrap: wrap;
  gap: 1rem;
  margin: 2rem 1rem 2rem 1rem;
}

#current-player-container h1 {
  margin: 0;
}
</style>