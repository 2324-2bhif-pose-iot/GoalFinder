<script setup>

</script>

<template>
  <div>
    <div class="card-title">Status: Not connected</div>
    <div class="card mb-3">
      <div class="card-header">
        Networks
      </div>
      <ul class="list-group list-group-flush networks-container">
        <li class="list-group-item list-group-item-action">Network 1</li>
        <li class="list-group-item list-group-item-action">Network 2</li>
      </ul>
    </div>
    <button class="btn btn-primary">Refresh</button>
  </div>
</template>

<style scoped>
  .networks-container {
    overflow-y: scroll;
    max-height: 12.7rem;
  }
</style>