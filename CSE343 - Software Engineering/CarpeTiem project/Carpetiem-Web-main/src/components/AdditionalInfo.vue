<template>
  <h5 class="mb-3">Çalışma Saatleri</h5>
  <div class="row g-3">
    <div class="col-12" v-for="index in workingDaysTr.length" :key="index">
      <div class="row align-items-center">
        <div class="col-3">
          <label
            :for="'workhours-' + workingDaysEng.at(index - 1) + '-start'"
            class="col-form-label"
            >{{ workingDaysTr.at(index - 1) }}</label
          >
        </div>
        <div class="col-3">
          <input
            type="text"
            class="form-control text-end"
            :id="'workhours-' + workingDaysEng.at(index - 1) + '-start'"
            v-model="workingHoursStart[index - 1]"
            autocomplete="off"
            :disabled="closed[index - 1].isClosed"
            @focus="
              setCaretPos($event, 2);
              isFraction = false;
            "
            @click="
              setCaretPos($event, 2);
              isFraction = false;
            "
            @keydown="enforceFormat($event, false)"
          />
        </div>
        -
        <div class="col-3">
          <input
            type="text"
            class="form-control text-end"
            :id="'workhours-' + workingDaysEng.at(index - 1) + '-end'"
            v-model="workingHoursEnd[index - 1]"
            autocomplete="off"
            :disabled="closed[index - 1].isClosed"
            @focus="
              setCaretPos($event, 2);
              isFraction = false;
            "
            @click="
              setCaretPos($event, 2);
              isFraction = false;
            "
            @keydown="enforceFormat($event, false)"
          />
        </div>
        <div class="col-2" v-if="workingDaysEng.at(index - 1) != 'weekdays'">
          <div class="form-check">
            <input
              class="form-check-input"
              type="checkbox"
              value=""
              :id="workingDaysEng.at(index - 1) + '-closed'"
              v-model="closed[index - 1].isClosed"
              @change="
                workingHoursStart[index - 1] = '00.00';
                workingHoursEnd[index - 1] = '00.00';
              "
            />
            <label
              class="form-check-label"
              :for="workingDaysEng.at(index - 1) + '-closed'"
            >
              Kapalı
            </label>
          </div>
        </div>
      </div>
    </div>
  </div>
  <h5 class="mb-3 mt-3">Halı Türlerine Göre Fiyatlandırma</h5>
  <div class="row align-items-center">
    <div class="col-5">
      <input
        type="text"
        class="form-control"
        id="carpet-type"
        placeholder="Halı Tipi"
        autocomplete="off"
        v-model="carpetType"
        @keydown.enter="addCarpetType"
      />
    </div>
    :
    <div class="col-3">
      <input
        type="text"
        class="form-control text-end"
        id="carpet-price"
        @focus="
          setCaretPos($event, 2);
          isFraction = false;
        "
        @click="
          setCaretPos($event, 2);
          isFraction = false;
        "
        @keydown="enforceFormat($event, true)"
        @keydown.enter="addCarpetType"
        autocomplete="off"
        v-model="carpetPrice"
      />
    </div>
  </div>
  <p
    class="mt-3"
    id="show-carpets"
    data-bs-toggle="modal"
    data-bs-target="#entered-carpets"
  >
    Halı Tiplerini Görüntüle
  </p>
  <div class="modal fade" tabindex="-1" id="entered-carpets">
    <div class="modal-dialog modal-dialog-scrollable modal-dialog-centered">
      <div class="modal-content">
        <div class="modal-header">
          <h5 class="modal-title">Halı Tipleri ve Fiyatlandırmaları</h5>
          <button
            type="button"
            class="btn-close"
            data-bs-dismiss="modal"
            aria-label="Close"
          ></button>
        </div>
        <div class="modal-body" v-if="Object.keys(pricePerType).length != 0">
          <div
            class="row align-items-center"
            v-for="(key, index) in Object.keys(pricePerType)"
            :key="key"
          >
            <div class="col-10">
              {{ index + 1 + ") " + key + ": " + pricePerType[key] + " ₺" }}
            </div>
            <div class="col-2">
              <button
                class="btn btn-outline-danger d-flex btn-sm"
                style="border: none; border-radius: 50%"
                type="button"
                @click="delete pricePerType[key]"
              >
                <i class="bi bi-trash pt-1 px-1" style="font-size: 1.1rem"></i>
              </button>
            </div>
          </div>
        </div>
        <div class="modal-body" v-else>
          Herhangi bir fiyatlandırma girilmedi.
        </div>
      </div>
    </div>
  </div>
  <div class="row justify-content-end mt-1">
    <div class="col-4 text-end">
      <button class="btn" type="button" @click="updateFirm">Devam Et</button>
    </div>
  </div>
</template>

<script>
import { ref } from "@vue/reactivity";
import db, { auth } from "../firebase";
import { useRouter } from "vue-router";
export default {
  name: "AdditionalInfo",
  setup() {
    const carpetType = ref("");
    const carpetPrice = ref("00.00 ₺");
    const workingDaysTr = ref(["Hafta İçi", "Cumartesi", "Pazar"]);
    const workingDaysEng = ref(["weekdays", "sat", "sun"]);
    const closed = ref([
      { isClosed: false },
      { isClosed: false },
      { isClosed: false },
    ]);
    const workingHoursStart = ref(["00.00", "00.00", "00.00"]);
    const workingHoursEnd = ref(["00.00", "00.00", "00.00"]);
    const pricePerType = ref({});
    const error = ref(false);
    var isFraction = ref(false);
    var fracCounts = [0, 0, 0, 0, 0, 0, 0];
    var intCounts = [0, 0, 0, 0, 0, 0, 0];
    const router = useRouter();

    const setCaretPos = (event, pos) => {
      event.target.setSelectionRange(pos, pos);
    };

    const isNumericInput = (event) => {
      const key = event.keyCode;
      return (
        (key >= 48 && key <= 57) || // Allow number line
        (key >= 96 && key <= 105) // Allow number pad
      );
    };

    const isModifierKey = (event) => {
      const key = event.keyCode;
      return (
        event.shiftKey === true ||
        key === 35 ||
        key === 36 || // Allow Shift, Home, End
        key === 9 ||
        key === 13 ||
        key === 46 || // Allow Tab, Enter, Delete
        // Allow Ctrl/Command + A,C,V,X,Z
        ((event.ctrlKey === true || event.metaKey === true) &&
          (key === 65 || key === 67 || key === 86 || key === 88 || key === 90))
      );
    };

    const enforceFormat = (event, isCurrency) => {
      var split = event.target.value.split(".");
      var idSplit = event.target.id.split("-");
      var workingDayIndex = workingDaysEng.value.indexOf(idSplit.at(1));
      var index = isCurrency
        ? fracCounts.length - 1
        : workingDayIndex +
          (idSplit.at(2) == "start" ? 0 : 1) +
          1 * workingDayIndex;

      if (!isNumericInput(event) && !isModifierKey(event)) {
        event.preventDefault();
        if (event.keyCode == 190) {
          setCaretPos(event, 5);
          isFraction.value = true;
        }
        if (event.keyCode == 8) {
          if (isFraction.value) {
            event.target.value =
              split.at(0) + ".0" + split.at(1).at(0) + (isCurrency ? " ₺" : "");
            setCaretPos(event, 5);
            if (fracCounts[index] > 0) {
              fracCounts[index]--;
            }
          } else {
            event.target.value = "0" + split.at(0).at(0) + "." + split.at(1);
            setCaretPos(event, 2);
            if (intCounts[index] > 0) {
              intCounts[index]--;
            }
          }
        }
      } else if (isNumericInput(event)) {
        if (isFraction.value) {
          if (fracCounts[index] < 2) {
            event.target.value =
              split.at(0) +
              "." +
              split.at(1).at(1) +
              event.key +
              (isCurrency ? " ₺" : "");
            setCaretPos(event, 5);
            if (event.key == "0" && fracCounts[index] > 0) {
              fracCounts[index]--;
            } else if (event.key != "0" && fracCounts[index] < 2) {
              fracCounts[index]++;
            }
          }
          event.preventDefault();
        } else {
          if (intCounts[index] < 2) {
            event.target.value =
              split.at(0).at(1) + event.key + "." + split.at(1);
            setCaretPos(event, 2);
            if (event.key == "0" && intCounts[index] > 0) {
              intCounts[index]--;
            } else if (event.key != "0" && intCounts[index] < 2) {
              intCounts[index]++;
            }
          }
          event.preventDefault();
        }
      }

      index = index != 0 && index != 1 ? index - 1 * workingDayIndex : index;
      index = idSplit.at(2) == "end" ? index - 1 : index;

      if (isCurrency) {
        carpetPrice.value = event.target.value;
      }

      if (!isCurrency && idSplit.at(2) == "start") {
        workingHoursStart.value[index] = event.target.value;
      }

      if (!isCurrency && idSplit.at(2) == "end") {
        workingHoursEnd.value[index] = event.target.value;
      }
    };

    const updateFirm = () => {
      let user = auth.currentUser;
      db.collection("firms")
        .doc(user.uid)
        .update({
          prices: pricePerType.value,
          workingHours: {
            WeekDays: {
              opening: workingHoursStart.value.at(0),
              closing: workingHoursEnd.value.at(0),
              isClosed: closed.value.at(0).isClosed,
            },
            Saturday: {
              opening: workingHoursStart.value.at(1),
              closing: workingHoursEnd.value.at(1),
              isClosed: closed.value.at(1).isClosed,
            },
            Sunday: {
              opening: workingHoursStart.value.at(2),
              closing: workingHoursEnd.value.at(2),
              isClosed: closed.value.at(2).isClosed,
            },
          },
        });

      db.collection("firms")
        .doc("index")
        .get()
        .then((doc) => {
          let dbTypes = doc.data().types;
          let enteredTypes = Object.keys(pricePerType.value);
          enteredTypes.forEach((type) => {
            if (!dbTypes.includes(type)) {
              dbTypes.push(type);
            }
          });
          db.collection("firms").doc("index").update({
            types: dbTypes,
          });
        });
      router.replace("/");
    };

    const addCarpetType = () => {
      pricePerType.value[carpetType.value] = parseFloat(
        carpetPrice.value.substring(0, 5)
      );
      carpetType.value = "";
      carpetPrice.value = "00.00 ₺";
      isFraction.value = false;
      fracCounts[fracCounts.length - 1] = 0;
      intCounts[intCounts.length - 1] = 0;
      document.getElementById("carpet-type").focus();
    };

    return {
      setCaretPos,
      enforceFormat,
      isFraction,
      workingDaysTr,
      workingDaysEng,
      closed,
      carpetType,
      carpetPrice,
      updateFirm,
      addCarpetType,
      workingHoursStart,
      workingHoursEnd,
      pricePerType,
    };
  },
};
</script>

<style scoped>
.btn:not(.btn-outline-danger) {
  background-color: rgb(120, 150, 120);
  border: rgb(120, 150, 120);
}

#show-carpets:hover,
.btn:not(.btn-outline-danger):hover {
  filter: brightness(85%);
}

.btn:not(.btn-outline-danger):focus {
  box-shadow: 0 0 0 0.25rem rgb(120 150 120 / 25%);
}

#show-carpets {
  color: rgb(120, 150, 120);
  cursor: pointer;
}
</style>
