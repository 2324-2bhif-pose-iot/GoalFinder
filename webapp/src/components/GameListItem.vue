<script>
export default {
  props: {
    teamOne: String,
    teamTwo: String,
    goalsTeamOne: Number,
    goalsTeamTwo: Number,
    playTime: Number
  }
}
</script>

<template>
  <strong> {{playTime}} min </strong>
  <p>{{teamOne}} <span>{{goalsTeamOne}}</span></p>
  <p>{{teamTwo}} <span>{{goalsTeamTwo}}</span></p>
</template>

<style scoped>

</style>