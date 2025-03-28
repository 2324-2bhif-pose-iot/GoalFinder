<script setup lang="ts">
import Page from "@/components/Page.vue";
import Button from "@/components/Button.vue";
import InputForm from "@/components/InputForm.vue";
import {reactive, ref, useTemplateRef} from "vue";
import {ShotChallengeGame} from "@/models/game";
import {Player} from "@/models/player";
import ToggleButton from "@/components/ToggleButton.vue";
import PlayIcon from "@/components/icons/PlayIcon.vue";
import {useSettingsStore} from "@/stores/settings";

const game = reactive(new ShotChallengeGame());
const showLeaderboard = ref(false);
const playerName = ref("");
const settings = useSettingsStore();

const addPlayerForm = useTemplateRef<HTMLFormElement>("add-player-form");

function recordShot(index: number, isHit: boolean) {
  if (isHit) {
    game.addHitToPlayer(index);

    //efgdrgerwger

  } else {
    game.addMissToPlayer(index);
  }
}

function finish() {
  showLeaderboard.value = true;
}

function restart() {
  showLeaderboard.value = false;
  game.reset();
}

function onPlayerAddFormSubmit() {
  game.addPlayer(new Player(playerName.value));
  addPlayerForm.value!.reset();
}

function onGameStartBtnClick() {
  if(game.isRunning) {
    game.pause();
    settings.isSoundEnabled = false;
  }
  else {
    game.start();
  }
}

</script>

<template>
  <Page :title="$t('header.game_shot_challenge')">
    <div class="basketball-shot-tracker" v-if="!showLeaderboard">
      <form ref="add-player-form" @submit.prevent="onPlayerAddFormSubmit">
        <div>
          <label for="player-name-input">{{ $t("word.add_person") }}</label>
          <InputForm id="player-name-input" v-model="playerName"/>
        </div>
        <div class="buttons-container">
          <Button type="submit">{{ $t("word.add_person") }}</Button>
          <ToggleButton readonly id="game-state-button" v-model="game.isRunning" @click="onGameStartBtnClick">
            <PlayIcon id="play-icon"/>
          </ToggleButton>
        </div>
      </form>

      <div v-if="game.players.length" id="current-player-container">
        <h1>{{ game.timer }}</h1>
        <h1>{{ game.getSelectedPlayer().name }}</h1>
      </div>

      <div v-if="game.players.length">
        <h3>{{ $t("word.person_list") }}</h3>
        <table id="player-list">
          <thead>
            <tr>
              <th>Player</th>
              <th>Hits</th>
              <th>Misses</th>
              <th>Edit</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="(person, index) in game.players" :key="index">
              <td>{{ person.name }}</td>
              <td>{{ person.hits }}</td>
              <td>{{ person.misses }}</td>
              <td>
                <div class="buttons-container">
                  <Button primary @click="recordShot(index, true)">{{ $t("word.hit") }}</Button>
                  <Button @click="recordShot(index, false)" severity="warning">{{ $t("word.miss") }}</Button>
                  <Button @click="game.removePlayer(index)" severity="danger">{{ $t("word.remove") }}</Button>
                </div>
              </td>
            </tr>
          </tbody>
        </table>
      </div>

      <div v-if="game.players.length">
        <Button primary @click="finish">{{ $t("word.finish") }}</Button>
      </div>
    </div>

    <div class="leaderboard" v-else>
      <h2>{{ $t("word.leaderboard") }}</h2>
      <ul>
        <li v-for="(person, index) in game.sortedPlayers" :key="index">
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

#player-list {
  width: 100%;
  margin-bottom: 1.5rem;
}

#player-list th {
  text-align: left;
}

#player-list td {
  padding: 1rem 0 0 0.2rem;
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
  display: inline-flex;
  flex-basis: content;
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

#game-state-button {
  padding: 0 0.4rem 0 0.4rem;
  display: flex;
  vertical-align: center;
  justify-content: center;
}

#play-icon {
  width: 1.4rem;
}
</style>